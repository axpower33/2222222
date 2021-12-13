#include <stdlib.h>
#include <fcntl.h>
#include <conio.h>
#include <io.h>
#include <sys\stat.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include<direct.h>
#define Rmx 30

#include "stdafx.h"
#include "FRSHELL.h"

#include "fr3ddoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//
// class CFR3dDoc
//

IMPLEMENT_DYNCREATE(CFR3dDoc, CDocument)

BEGIN_MESSAGE_MAP(CFR3dDoc, CDocument)
        //{{AFX_MSG_MAP(CFR3dDoc)
        // Handlers within the section marked by {{AFX_MSG_MAP and }}AFX_MSG_MAP
        // are maintained by ClassExpress.
        //}}AFX_MSG_MAP

END_MESSAGE_MAP()

//
// CFR3dDoc constructor
//

float kk=1.38E-23;
float E0=8.854E-14;
int E=100;
float C_SI=1/(4*M_PI*E0*E);
float eQulon=1.6E-19;
char getcd[128];


CFR3dDoc::CFR3dDoc()
{
 randomize();
 Rmax=FrMInCnd->m_Rmax;
 Rmin=FrMInCnd->m_Rmin;
 Rmid=FrMInCnd->m_Rmid;
 MaxQ=FrMInCnd->m_Q;
 Tmshft=0.0001;
 DensAg=10.5;
 Tk=300;
}

//
// CFR3dDoc destructor
//

CFR3dDoc::~CFR3dDoc()
{
  DistroyArray();
}

BOOL CFR3dDoc::OnNewDocument()
{ if (!CDocument::OnNewDocument())
  {
    return FALSE;
  }
  else
  { needCharge=false;
    FrMInCnd->DoModal();
    N=FrMInCnd->m_Npat;
    dt=FrMInCnd->m_dt;
    t=0;
    s=1;
    Xmax=Ymax=Zmax=sqrt(N)*(2*Rmax+Rmid)/2;
    GetminX=-Xmax;
    GetminY=-Ymax;
    GetmaxX=Xmax;
    GetmaxY=Ymax;
    GetScX=(GetmaxX-GetminX);
    GetScY=(GetmaxY-GetminY);
    MakeArray(N);
    InitParticle();
    InitAgr();
    return TRUE;
  }

}

char* CFR3dDoc::PathToDat()
{
  char path[128];
  path[0]=0;
  strcat(path,getcd);
  strcat(path,"\\");
  strcat(path,CPathDlg->m_path);
  strcat(path,"\\");
  return path;
}

void CFR3dDoc::Serialize(CArchive& ar)
{
 if (ar.IsStoring())
  {
    ar.Write(&N, sizeof(N));
    for (Pi=FirstPat;Pi!=NULL;Pi=Pi->next)
    ar.Write(Pi,sizeof(Particle));
    ar.Write(&dt, sizeof(dt));
    ar.Write(&t, sizeof(t));
    ar.Write(CMass,(N/2+1)*sizeof(*CMass));
    ar.Write(Pagregat,(N/2+1)*sizeof(*Pagregat));
    ar.Write(ConPat,(N+1)*sizeof(*ConPat));
    ar.Write(&s, sizeof(s));

  }
  else
  {
    ar.Read (&N, sizeof(N));
    MakeArray(N);
    TempP=new Particle;
     for(Pi=FirstPat;Pi!=NULL;Pi=Pi->next)
     {  TempP->next=Pi->next;
        TempP->pred=Pi->pred;
        ar.Read(Pi,sizeof(Particle));
        Pi->next=TempP->next;
        Pi->pred=TempP->pred;
     }
    delete TempP;
    ar.Read (&dt, sizeof(t));
    ar.Read (&t, sizeof(t));
    ar.Read (CMass,(N/2+1)*sizeof(*CMass));
    ar.Read (Pagregat,(N/2+1)*sizeof(*Pagregat));
    ar.Read (ConPat,(N+1)*sizeof(*ConPat));
    ar.Read (&s, sizeof(s));
    Xmax=Ymax=Zmax=sqrt(N)*(2*Rmax+Rmid)/2;
    GetminX=-Xmax;
    GetminY=-Ymax;
    GetmaxX=Xmax;
    GetmaxY=Ymax;
    GetScX=(GetmaxX-GetminX);
    GetScY=(GetmaxY-GetminY);

  }
}

void CFR3dDoc::OnIdle()
{  if (FirstPat->q) CulonForces();

   for (Pi=FirstPat;Pi!=NULL;Pi=Pi->next)
   for (Pj=Pi->next;Pj!=NULL;Pj=Pj->next)
   { float dist_ij=pow(Pi->X-Pj->X,2)+pow(Pi->Y-Pj->Y,2)+pow(Pi->Z-Pj->Z,2);
      if (dist_ij<=pow((Pi->R+Pj->R),2)) UnitPaticle(Pi,Pj);
    }
    AgrForces();
    MovePart();
    t=t+dt;
    SetModifiedFlag();
}

//
// CFR3dDoc debug diagnostics
//

#ifdef _DEBUG
void CFR3dDoc::AssertValid() const
{
        CDocument::AssertValid();
}

void CFR3dDoc::Dump(CDumpContext& dc) const
{
        CDocument::Dump(dc);
}
#endif

void CFR3dDoc::MakeArray(int N)
{   FirstPat=new Particle;
    FirstPat->pred=NULL;
    FirstPat->N=1;
    LastPat=FirstPat;
    for(int i=2;i!=N+1;i++)
    {  LastPat->next=TempP=new Particle;
       TempP->pred=LastPat;
       TempP->next=NULL;
       TempP->N=i;
       LastPat=TempP;
    }
    dF= new Agregat[N/2];
    CMass= new Agregat[N/2];
    Pagregat= new int[N/2] ;
    ConPat= new int[N];

}

void CFR3dDoc::DistroyArray()
{ for(TempP=FirstPat->next;TempP->next!=NULL;TempP=TempP->next)
  delete TempP->pred;
  delete TempP;

  delete[] ConPat;
  delete[] Pagregat;
  delete[] CMass;
  delete[] dF;
}

Particle* CFR3dDoc::Npat(int Np)
{ TempP=FirstPat;
  for(int i=1;i<Np;i++) TempP=TempP->next;
  return (TempP);
}

void CFR3dDoc::MxwDstr()
{ const Vmin=0;
  float Vmax=0.25;
  int kmax=N/3;
  int i,j;
  double F;
  float dN,V,Vel,dv,alpha,theta;
  int rdn ;

  j=0; i=1;
  dv=(Vmax-Vmin)/kmax;

  Pj=FirstPat;

  for(Pi=FirstPat;Pi!=NULL;Pi=Pi->next)
  {  V=Vmin+dv*i;
     F=sqrt(Pi->mass/(2*M_PI*kk*Tk));
     F=pow(F,3);
     F=F*exp(-(Pi->mass*pow(V,2))/(2*kk*Tk))*4*M_PI*pow(V,2);
     dN=N*F*dv;

     rdn=(int)dN;
     i++;
     if ((j+rdn)<N)
     while (rdn)
     { j++;
       Vel=V;
       alpha=2*M_PI* float(rand())/RAND_MAX;
       theta=2*M_PI* float(rand())/RAND_MAX;
       Pj->Vx=Vel*cos(theta)*sin(alpha);
       Pj->Vy=Vel*cos(theta)*cos(alpha);
       Pj->Vz=Vel*sin(theta);
       rdn--;
       Pj=Pj->next;
     }
  }
  int cnt=N-j;

  while (cnt--)
  { Vel=sqrt((8*kk*Tk)/(M_PI*Pj->mass));
    alpha=2*M_PI*float(rand())/RAND_MAX;
    theta=2*M_PI*float(rand())/RAND_MAX;
    Pj->Vx=Vel*cos(theta)*sin(alpha);
    Pj->Vy=Vel*cos(theta)*cos(alpha);
    Pj->Vz=Vel*sin(theta);
    Pj=Pj->next;
  }
}

void CFR3dDoc::InitParticle()
{   int sign=0;
    float sq,alpha;
    for(Pi=FirstPat;Pi!=NULL;Pi=Pi->next)
    { sign=1-sign;
m1: Pi->X=-Xmax+GetScX*float(rand())/RAND_MAX;
    Pi->Y=-Ymax+GetScY*float(rand())/RAND_MAX;
    Pi->Z=-Xmax+GetScX*float(rand())/RAND_MAX;

    Pi->R=Rmax-(Rmax-Rmin)*float(rand())/RAND_MAX;
/*  if (Pi->N<=N*0.2) Pi->R=Rmin;
    else if (Pi->N<=N*0.8) Pi->R=(Rmin+Rmax)/2;
    else Pi->R=Rmax;
*/

    for(Pj=FirstPat;Pj!=Pi;Pj=Pj->next)
    { float dist_ij=pow(Pi->X-Pj->X,2)+pow(Pi->Y-Pj->Y,2)+pow(Pi->Z-Pj->Z,2);
      if (dist_ij<=pow(Pi->R+Pj->R,2)) goto m1;
    }
    if (needCharge) if (sign) Pi->q=MaxQ*eQulon;
    else Pi->q=-MaxQ*eQulon;
    else Pi->q=0;

    Pi->mass=4/3*M_PI*pow(Pi->R,3)/DensAg;
    //TmPat[Pi->N]=Tmshft*float(rand())/RAND_MAX;

    Pi->agr=0;
    Pi->stop=false;
    Pi->VanX=0;
    Pi->VanY=0;
    Pi->VanZ=0;
    Pi->Fx=0;
    Pi->Fy=0;
    Pi->Fz=0;
   }
   MxwDstr();
}

void CFR3dDoc::InitAgr()
{
 int c;
 for(c=0;c!=N/2;c++) Pagregat[c]=0;
 for(c=0;c!=N+1;c++) ConPat[c]=0;
}

bool CFR3dDoc::IsPatInAgr (Particle* Pi,Particle* Pj)
{
  return  (bool) ((Pi->agr!=0)&&(Pi->agr==Pj->agr));
}

void CFR3dDoc::CulonForces()
{ int Nagr;
  float Temp, dX, dY, dZ;
  for (Pi=FirstPat;Pi!=NULL;Pi=Pi->next)
  { Pi->Fx=0;
    Pi->Fy=0;
    Pi->Fz=0;
  }
  for (Pi=FirstPat; Pi!=NULL;Pi=Pi->next)
  { for (Pj=Pi->next;Pj!=NULL;Pj=Pj->next)
    { if (IsPatInAgr(Pi,Pj)) continue;
      dX=Pi->X-Pj->X;
      dY=Pi->Y-Pj->Y;
      dZ=Pi->Z-Pj->Z;
      Temp=Pi->q*Pj->q/pow(dX*dX+dY*dY+dZ*dZ,1.5);
      Pj->Fx-=Temp*dX;
      Pj->Fy-=Temp*dY;
      Pj->Fz-=Temp*dZ;
      Pi->Fx+=Temp*dX;
      Pi->Fy+=Temp*dY;
      Pi->Fz+=Temp*dZ;
    }
    Pi->Fx*=C_SI;
    Pi->Fy*=C_SI;
    Pi->Fz*=C_SI;
//  float U=Pi->Fx*dX+Pi->Fy*dY+Pi->Fz*dZ;
//  float Ek=Pi->mass*(pow(Pi->Vx,2)+pow(Pi->Vy,2)+pow(Pi->Vz,2))/2;
  }
}

void CFR3dDoc::MovePart()
{
 int i,j;
 char st[10];
 float dVx,dVy,dVz;

 for (Pi=FirstPat;Pi!=NULL;Pi=Pi->next)
 if (Pi->stop==false)
 { dVx=dt*Pi->Fx/Pi->mass;
   dVy=dt*Pi->Fy/Pi->mass;
   dVz=dt*Pi->Fz/Pi->mass;
   Pi->Vx+=dVx;
   Pi->Vy+=dVy;
   Pi->Vz+=dVz;
// RandWalk(TmPat[Pi->N],Pi->Vx,Pi->Vy,Pi->Vz);
   if ((Pi->X>GetmaxX)||(Pi->X<GetminX)) Pi->Vx=-Pi->Vx;
   if ((Pi->Y>GetmaxY)||(Pi->Y<GetminY)) Pi->Vy=-Pi->Vy;
   if ((Pi->Z>GetmaxX)||(Pi->Z<GetminX)) Pi->Vz=-Pi->Vz;
   Pi->X+=dt*Pi->Vx;
   Pi->Y+=dt*Pi->Vy;
   Pi->Z+=dt*Pi->Vz;
 }
}

void CFR3dDoc::AngleSpeed (int kk, RPoint &W)
{
   float Nx=0; float Ny=0; float Nz=0;

   int i=Pagregat[kk];
   while (i)
   { Nx+=(Pi->Y-CMass[kk].Y)*Pi->Fz-(Pi->Z-CMass[kk].Z)*Pi->Fy;
     Ny+=(Pi->Z-CMass[kk].Z)*Pi->Fx-(Pi->X-CMass[kk].X)*Pi->Fz;
     Nz+=(Pi->X-CMass[kk].X)*Pi->Fy-(Pi->Y-CMass[kk].Y)*Pi->Fx;
     i=ConPat[i];
   }
   CMass[kk].Mx+=dt*Nx;
   CMass[kk].My+=dt*Ny;
   CMass[kk].Mz+=dt*Nz;

   W.X=CMass[kk].Mx/CMass[kk].Jx;
   W.Y=CMass[kk].My/CMass[kk].Jy;
   W.Z=CMass[kk].Mz/CMass[kk].Jz;
}

void CFR3dDoc::ChangeCMass(int Nagr)
{
  int Np=Pagregat[Nagr];
  float Mass=0;
  CMass[Nagr].X=0;
  CMass[Nagr].Y=0;
  CMass[Nagr].Z=0;

  CMass[Nagr].Vx=0;
  CMass[Nagr].Vy=0;
  CMass[Nagr].Vz=0;

 while (Np)
 {
   PNp=Npat(Np);
   Mass+=PNp->mass;
   CMass[Nagr].X+=PNp->mass*PNp->X;
   CMass[Nagr].Y+=PNp->mass*PNp->Y;
   CMass[Nagr].Z+=PNp->mass*PNp->Z;

   CMass[Nagr].Vx+=PNp->mass*PNp->Vx;
   CMass[Nagr].Vy+=PNp->mass*PNp->Vy;
   CMass[Nagr].Vz+=PNp->mass*PNp->Vz;

   Np=ConPat[Np];
 }

   CMass[Nagr].X/=Mass;
   CMass[Nagr].Y/=Mass;
   CMass[Nagr].Z/=Mass;

   CMass[Nagr].Vx/=Mass;
   CMass[Nagr].Vy/=Mass;
   CMass[Nagr].Vz/=Mass;


  Np=Pagregat[Nagr];

  CMass[Nagr].Jx=0;
  CMass[Nagr].Mx=CMass[Nagr].My=CMass[Nagr].Mz=0;

 while (Np)
 { PNp=Npat(Np);
   CMass[Nagr].Jx+=PNp->mass*((pow(PNp->Z-CMass[Nagr].Z,2)+pow(PNp->Y-CMass[Nagr].Y,2))+0.4*pow(PNp->R,2));
   CMass[Nagr].Jy+=PNp->mass*((pow(PNp->X-CMass[Nagr].X,2)+pow(PNp->Z-CMass[Nagr].Z,2))+0.4*pow(PNp->R,2));
   CMass[Nagr].Jz+=PNp->mass*((pow(PNp->X-CMass[Nagr].X,2)+pow(PNp->Y-CMass[Nagr].Y,2))+0.4*pow(PNp->R,2));

   CMass[Nagr].Mx+=PNp->mass*((PNp->Y-CMass[Nagr].Y)*(PNp->Vz-CMass[Nagr].Vz)-(PNp->Z-CMass[Nagr].Z)*(PNp->Vy-CMass[Nagr].Vy));
   CMass[Nagr].My+=PNp->mass*((PNp->Z-CMass[Nagr].Z)*(PNp->Vx-CMass[Nagr].Vx)-(PNp->X-CMass[Nagr].X)*(PNp->Vz-CMass[Nagr].Vz));
   CMass[Nagr].Mz+=PNp->mass*((PNp->X-CMass[Nagr].X)*(PNp->Vy-CMass[Nagr].Vy)-(PNp->Y-CMass[Nagr].Y)*(PNp->Vx-CMass[Nagr].Vx));

   Np=ConPat[Np];
 }
}

float CFR3dDoc::GetMass (int i)
{ float ret=0;
  if (Pi->stop)
  { i=Pagregat[Pi->agr];
    do
    { ret+=Pi->mass;
      i=ConPat [i];
    } while(i!=0);
  } else ret = Pi->mass;
  return ret;
}


void CFR3dDoc::SetAgrSpeed(Particle* Pi)
{ RPoint W;
  if (Pi->stop)
  {
    //Вычисление линейной скорости частиц в агрегате }
    int i=Pagregat[Pi->agr];
    AngleSpeed(Pi->agr,W);
    do
    { Pi->Vx=CMass[Pi->agr].Vx + W.Y*(Pi->Z-CMass[Pi->agr].Z)-W.Z*(Pi->Y-CMass[Pi->agr].Y);
      Pi->Vy=CMass[Pi->agr].Vy + W.Z*(Pi->X-CMass[Pi->agr].X)-W.X*(Pi->Z-CMass[Pi->agr].Z);
      Pi->Vz=CMass[Pi->agr].Vz + W.X*(Pi->Y-CMass[Pi->agr].Y)-W.Y*(Pi->X-CMass[Pi->agr].X);
      i = ConPat[i];
    }while(i!=0);
  }
}

//  Добавляет j частицу к агрегату начинающемуся с i частиц
void CFR3dDoc::AddPattoAgr (Particle* Pi,Particle* Pj)
{ int i,j;
  i=Pi->N;
  j=Pj->N;
  Pj->agr=Pi->agr;

  while (ConPat[i]) i=ConPat[i];

  ConPat[i]=j;
  if (ConPat[j]!=0)
  {
   j=ConPat[j];
   while (j)
   {
     Pj=Npat(j);
     Pj->agr=Pi->agr;
     j=ConPat[j];
   }
  }
}

//      Рaздвигает две частиц
void CFR3dDoc::PushAway (Particle*Pi,Particle* Pj )
{ float dX, dY, dZ, R;

  R=Pi->R+Pj->R;
  dX=Pj->X-Pi->X;
  dY=Pj->Y-Pi->Y;
  dZ=Pj->Z-Pi->Z;

  float dist_ij=sqrt(dX*dX+dY*dY+dZ*dZ);

  dX*=(R-dist_ij)/dist_ij;
  dY*=(R-dist_ij)/dist_ij;
  dZ*=(R-dist_ij)/dist_ij;

  if (Pj->agr!=0)
  {
   CMass[Pj->agr].X+=dX;
   CMass[Pj->agr].Y+=dY;
   CMass[Pj->agr].Z+=dZ;
   int j=Pagregat[Pj->agr];
   while (j)
   {
     Pj=Npat(j);
     Pj->X+=dX;
     Pj->Y+=dY;
     Pj->Z+=dZ;

     j=ConPat[j];
   }
  } else
    {
      Pj->X+=dX;
      Pj->Y+=dY;
      Pj->Z+=dZ;
    }
}

void CFR3dDoc::UnitPaticle (Particle* Pi, Particle* Pj)
{
 int l, kk, m;
 int i=Pi->N;
 int j=Pj->N;

 Particle* Pm; Particle* Pl;

 if (IsPatInAgr(Pi,Pj)) return;


 PushAway (Pi,Pj);

 SetAgrSpeed(Pi);
 SetAgrSpeed(Pj);

 if (Pi->stop==false)
 {
   if (Pj->stop==false)
   {
    Pagregat[s]=Pi->N;
    Pi->agr=s;
    Pj->agr=s;
    s++;
    ConPat[i]=j;
   } else AddPattoAgr(Pj,Pi);

 } else
   if (Pj->stop==false) AddPattoAgr(Pi,Pj);
   else
   { kk=Pi->agr;
     l=Pagregat[kk];
     s--;
     Pagregat[kk]=Pagregat[s];
     Pagregat[s]=0;
     CMass[kk]=CMass[s];
     CMass[s].X=CMass[s].Y=CMass[s].Z=
     CMass[s].Vx=CMass[s].Vy=CMass[s].Vz=
     CMass[s].Mx=CMass[s].My=CMass[s].Mz=
     CMass[s].Jx=CMass[s].Jy=CMass[s].Jz=0;
     m=Pagregat[kk];
     while (m)
     {
      Pm=Npat(m);
      Pm->agr=kk;
      m=ConPat[m];
     }
     Pl=Npat(l);
     AddPattoAgr(Pj,Pl);
   }

   Pi->stop=true;
   Pj->stop=true;
   ChangeCMass (Pj->agr);
}

void CFR3dDoc::AgrForces()
{ int i,kk;
  float mass, dVx, dVy, dVz, dX, dY, dZ, M1;

  for(kk=1;kk<s;kk++)
  { i=Pagregat[kk];
    dF[kk].X=dF[kk].Y=dF[kk].Z=mass=0;

    while(i)
    { Pi=Npat(i);
      dF[kk].X+=Pi->Fx;
      dF[kk].Y+=Pi->Fy;
      dF[kk].Z+=Pi->Fz;
      mass+=Pi->mass;
      i=ConPat[i];
    }
    dVx=dt*dF[kk].X/mass;
    dVy=dt*dF[kk].Y/mass;
    dVz=dt*dF[kk].Z/mass;
    if ((CMass[kk].X>GetmaxX)||(CMass[kk].X<GetminX)) CMass[kk].Vx=-CMass[kk].Vx;
    if ((CMass[kk].Y>GetmaxY)||(CMass[kk].Y<GetminY)) CMass[kk].Vy=-CMass[kk].Vy;
    if ((CMass[kk].Z>GetmaxX)||(CMass[kk].Z<GetminX)) CMass[kk].Vz=-CMass[kk].Vz;
    CMass[kk].Vx+=dVx;
    CMass[kk].Vy+=dVy;
    CMass[kk].Vz+=dVz;
    CMass[kk].X+=dt*CMass[kk].Vx;
    CMass[kk].Y+=dt*CMass[kk].Vy;
    CMass[kk].Z+=dt*CMass[kk].Vz;

//-------- Вычисление угла Phi --------//
    RPoint phi;
    AngleSpeed(kk,phi);
    phi.X=dt*phi.X;
    phi.Y=dt*phi.Y;
    phi.Z=dt*phi.Z;
    //  Вращение агрегата посредством преобразования координат с помощью---//
                         //---- матрицы вращения ---//

    i=Pagregat[kk];
    while (i)
    {
      Pi=Npat(i);
      Pi->X+=dt*(CMass[kk].Vx+dVx);
      Pi->Y+=dt*(CMass[kk].Vy+dVy);
      Pi->Z+=dt*(CMass[kk].Vz+dVz);
      dX=Pi->X-CMass[kk].X;
      dY=Pi->Y-CMass[kk].Y;
      Pi->X=CMass[kk].X+dX*cos(phi.Z)-dY*sin(phi.Z);
      Pi->Y=CMass[kk].Y+dY*cos(phi.Z)+dX*sin(phi.Z);
      dY=Pi->Y-CMass[kk].Y;
      dZ=Pi->Z-CMass[kk].Z;
      Pi->Y=CMass[kk].Y+dY*cos(phi.X)-dZ*sin(phi.X);
      Pi->Z=CMass[kk].Z+dZ*cos(phi.X)+dY*sin(phi.X);

      dX=Pi->X-CMass[kk].X;
      dZ=Pi->Z-CMass[kk].Z;
      Pi->X=CMass[kk].X+dX*cos(phi.Y)-dZ*sin(phi.Y);
      Pi->Z=CMass[kk].Z+dZ*cos(phi.Y)+dX*sin(phi.Y);
      i=ConPat[i];
     }
   }
}

//
// CFR3dDoc commands
//
