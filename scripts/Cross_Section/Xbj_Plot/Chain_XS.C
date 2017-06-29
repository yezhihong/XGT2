/*Include{{{*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <errno.h>
#include <sstream>
//#include <iterator>
//from root
#include <TMath.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TLorentzVector.h>
#include <TMatrix.h>
#include <TFile.h>
#include <TH2F.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TLegend.h>
#include <TTree.h>
#include <TStopwatch.h>
/*}}}*/
using namespace::std;
using namespace::TMath;
#include "./XGT2_Main.h"
#include "/work/halla/e08014/disk1/yez/Cross_Section/SRC/XGT2_XEMC.h"

char* gFile1;
char* gFile2;
char* gFile3;
char* gFile4;
char* gTgt;
int getargs(int argc, char** argv);

/*Get_Target_Name{{{*/
TString gGet_Target_Name(const TString& aName){
	TString aTarget_Name="MM";

	if(aName.Contains("H2"))
		aTarget_Name="H2";
	else if(aName.Contains("He3"))
		aTarget_Name="He3";
	else if(aName.Contains("He4"))
		aTarget_Name="He4";
	else if(aName.Contains("C12"))
		aTarget_Name="C12";
	else if(aName.Contains("Ca40"))
		aTarget_Name="Ca40";
	else if(aName.Contains("Ca48"))
		aTarget_Name="Ca48";
	else
		cerr<<"*** I don't know the target name!!!"<<endl;
	return aTarget_Name;
}
/*}}}*/

/*Get_Kin_Name{{{*/
TString gGet_Kin_Name(const TString& aKin){
	TString aKin_Name="MM";
	if(aKin.Contains("3.1"))
		aKin_Name="3.1";
	else if(aKin.Contains("3.2"))
		aKin_Name="3.2";
	else if(aKin.Contains("4.1"))
		aKin_Name="4.1";
	else if(aKin.Contains("4.2"))
		aKin_Name="4.2";
	else if(aKin.Contains("5.0") && !aKin.Contains("5.05") )
		aKin_Name="5.0";
	else if(aKin.Contains("5.05"))
		aKin_Name="5.05";
	else if(aKin.Contains("5.1"))
		aKin_Name="5.1";
	else if(aKin.Contains("5.2"))
		aKin_Name="5.2";
	else if(aKin.Contains("6.5"))
		aKin_Name="6.5";
	else
		cerr<<"*** I don't know the kinematics name!!!"<<endl;
	return aKin_Name;
}
/*}}}*/
TString aFileName1, aFileName2, aFileName3,aFileName4;
TString Target;

/*Chain XS{{{*/
void ChainXS()
{  
	/*Define{{{*/
	double E0 = 3.356;
	//	TString Target = "C12";
	//	cerr<<"Target (H2,He3,He4,C12,Ca40,Ca48) = "; cin >> Target;
	double Theta = 21.00;
	TString Kin = "3.1";

	Double_t p,nu,Q2,xbj,angle,Ei,Ep,tmp,Livetime,Ntg,Ni,Nf_EX,Nf_SAMC,Nf_SAMC_Gen;
	Double_t XS,XS_Stat_Err,XS_Sys_Err,Yield_MC,Yield_EX,Y_MC_Sys_Err,Y_EX_Sys_Err,Y_MC_Stat_Err,Y_EX_Stat_Err;
	TString comment;
	Double_t pXS1[200], pXS_Err1[200], pXbj1[200],  pXbj_Err1[200],pXS_MC1[200],pYield_MC1[200],pYield_EX1[200],pYield_MC_Err1[200],pYield_EX_Err1[200];
	Double_t pXS2[200], pXS_Err2[200], pXbj2[200],  pXbj_Err2[200],pXS_MC2[200],pYield_MC2[200],pYield_EX2[200],pYield_MC_Err2[200],pYield_EX_Err2[200];
	Double_t pXS3[200], pXS_Err3[200], pXbj3[200],  pXbj_Err3[200],pXS_MC3[200],pYield_MC3[200],pYield_EX3[200],pYield_MC_Err3[200],pYield_EX_Err3[200];
	Double_t pXS4[200], pXS_Err4[200], pXbj4[200],  pXbj_Err4[200],pXS_MC4[200],pYield_MC4[200],pYield_EX4[200],pYield_MC_Err4[200],pYield_EX_Err4[200];

	Double_t pY_R1[200],pY_R2[200],pY_R_Err1[200],pY_R_Err2[200];
	Double_t pY_R3[200],pY_R4[200],pY_R_Err3[200],pY_R_Err4[200];
	/*}}}*/

	/*First{{{*/
	TString infile1 = aFileName1;
	cerr<<"==== Reading 1st file from "<<infile1<<endl;
	ifstream run_1; run_1.open(infile1);

	Int_t Count1 =0;
	// Target = gGet_Target_Name(infile1.Data());
	Kin = gGet_Kin_Name(infile1.Data());

	TString Arm1="X";
	if(infile1.Contains("L_"))
		Arm1="L";
	else if(infile1.Contains("R_"))
		Arm1="R";


	if(Kin=="MM"){
		cerr<<"1st: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
	}
	if(Kin=="3.1"||Kin=="3.2")
		Theta = 21.00; 
	else if(Kin=="4.1"||Kin=="4.2")
		Theta = 23.00;
	else if(Kin=="5.05"||Kin=="5.0"||Kin=="5.1"||Kin=="5.2")
		Theta =  25.00;
	else if(Kin=="6.5")
		Theta = 28.00;
	else
		cerr<<"*** ERROR, unknown kinematics setting!"<<endl;

	TString Kin_Name1 = Form("Kin%s",Kin.Data());

	Get_XS* xs1 = new Get_XS();
	//xs1->Load_Table_ByKin(Target.Data(),Kin_Name1.Data());
	xs1->Load_Table(Target.Data(),Kin_Name1.Data());

	comment.ReadLine(run_1);
	while ( run_1>>XS>>XS_Stat_Err>>XS_Sys_Err>>xbj>>angle>>Ep>>nu>>Q2>>Ei>>p>>Livetime>>Ntg>>Ni>>Nf_EX>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Sys_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Sys_Err )
	{
		//	if(XS_Stat_Err<0.0){
		//		Y_EX_Stat_Err = Yield_EX * sqrt(1./Nf_EX+1./Ni);
		//		XS_Stat_Err = XS * sqrt( pow(Y_EX_Stat_Err/Yield_EX,2)+pow(Y_MC_Stat_Err/Yield_MC,2));
		//	}
		//		XS*=1e33; XS_Stat_Err*=1e33;  XS_Sys_Err *= 1e33; //From cm^2/MeV/sr to nb/MeV/sr
		//		Yield_EX*=1e33; Y_EX_Stat_Err*=1e33; Y_EX_Sys_Err*=1e33;
		if ( angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Sys_Err,2)+pow(XS_Stat_Err,2))/XS <0.2)
		{
			pXS1[Count1] = XS;      pXS_Err1[Count1] = XS_Stat_Err;
			pXbj1[Count1] = xbj;    pXbj_Err1[Count1] = 0.0;

			pYield_MC1[Count1]=Yield_MC; 
			pYield_EX1[Count1]=Yield_EX;
			pYield_MC_Err1[Count1]=Y_MC_Stat_Err; 
			pYield_EX_Err1[Count1]=Y_EX_Stat_Err;
			pY_R1[Count1]=Yield_EX/Yield_MC;
			pY_R_Err1[Count1]=pY_R1[Count1] * sqrt( pow(Y_EX_Stat_Err/Yield_EX,2) + pow(Y_MC_Stat_Err/Yield_MC,2) );

			pXS_MC1[Count1] = xs1->gGet_XS_Born(E0,Ep,Theta);
			//pXS_MC1[Count1] = xs1->gGet_XS_Born_ByKin(E0,Ep/1000.0,Theta);

			//cerr << Form("   --Xbj = %f, XS_EX = %e, XS_MC=%e ", xbj, XS, pXS_MC1[Count1] ) <<endl;
			if(Min_Yield>=Yield_MC&&Yield_MC>=1e3)
				Min_Yield = Yield_MC;
			if(Max_Yield<=Yield_MC)
				Max_Yield = Yield_MC;
			if(Min_Yield>=Yield_EX&&Yield_EX>=1e3)
				Min_Yield = Yield_EX;
			if(Max_Yield<=Yield_EX)
				Max_Yield = Yield_EX;

			if(Min_X>=xbj)
				Min_X = xbj;	
			if(Max_X<=xbj)
				Max_X = xbj;

			if(Min>=XS)
				Min = XS;	
			if(Max<=XS)
				Max = XS;
			if(Min>= pXS_MC1[Count1])
				Min =  pXS_MC1[Count1];	
			if(Max<= pXS_MC1[Count1])
				Max =  pXS_MC1[Count1];

			if(Min_R>=pY_R1[Count1])
				Min_R = pY_R1[Count1];
			if(Max_R<=pY_R1[Count1])
				Max_R = pY_R1[Count1];

			Count1++;
		}
		if ( !run_1.good() )
			break;
	}
	run_1.close();
	delete xs1;
	cerr << "  Total XS Points for 1st = " << Count1 <<endl;
	/*}}}*/

	/*Second{{{*/
	TString Kin_Name2 ="";
	Bool_t bMore = kTRUE;
	TString infile2 = aFileName2;
	cerr<<"==== Reading 2nd file from "<<infile2<<endl;
	TString Arm2="X";
	if(infile2 =="x")
		bMore = kFALSE;
	if(infile1.Contains("L_"))
		Arm2="L";
	else if(infile1.Contains("R_"))
		Arm2="R";

	Int_t Count2=0;
	if(bMore){
		ifstream run_2; run_2.open(infile2);
		//	Target = gGet_Target_Name(infile2.Data());
		Kin = gGet_Kin_Name(infile2.Data());
		if(Kin=="MM"){
			cerr<<"2nd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
		}
		if(Kin=="3.1"||Kin=="3.2")
			Theta = 21.00;
		else if(Kin=="4.1"||Kin=="4.2")
			Theta = 23.00;
		else if(Kin=="5.0"||Kin=="5.05"||Kin=="5.1"||Kin=="5.2")
			Theta =  25.00;
		else if(Kin=="6.5")
			Theta = 28.00;
		else
			cerr<<"*** ERROR, unknown kinematics setting!"<<endl;
		Kin_Name2 = Form("Kin%s",Kin.Data());
		Get_XS* xs2 = new Get_XS();
		xs2->Load_Table(Target.Data(),Kin_Name2.Data());
		//xs2->Load_Table_ByKin(Target.Data(),Kin_Name2.Data());

		comment.ReadLine(run_2);
		while ( run_2>>XS>>XS_Stat_Err>>XS_Sys_Err>>xbj>>angle>>Ep>>nu>>Q2>>Ei>>p>>Livetime>>Ntg>>Ni>>Nf_EX>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Sys_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Sys_Err )
		{

			//		if(XS_Stat_Err<0.0){
			//		  Y_EX_Stat_Err = Yield_EX * sqrt(1./Nf_EX+1./Ni);
			//		  XS_Stat_Err = XS * sqrt( pow(Y_EX_Stat_Err/Yield_EX,2)+pow(Y_MC_Stat_Err/Yield_MC,2));
			//		}
			//			XS*=1e33; XS_Stat_Err*=1e33;  XS_Sys_Err *= 1e33; //From cm^2/MeV/sr to nb/MeV/sr
			//            Yield_EX*=1e33; Y_EX_Stat_Err*=1e33; Y_EX_Sys_Err*=1e33;
			if ( angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Sys_Err,2)+pow(XS_Stat_Err,2))/XS <0.2)
			{
				pXS2[Count2] = XS;      pXS_Err2[Count2] = XS_Stat_Err;
				pXbj2[Count2] = xbj;    pXbj_Err2[Count2] = 0.0;
				pYield_MC2[Count2]=Yield_MC; 
				pYield_EX2[Count2]=Yield_EX;
				pYield_MC_Err2[Count2]=Y_MC_Stat_Err; 
				pYield_EX_Err2[Count2]=Y_EX_Stat_Err;
				pY_R2[Count2]=Yield_EX/Yield_MC;
				pY_R_Err2[Count2]=pY_R2[Count2] * sqrt( pow(Y_EX_Stat_Err/Yield_EX,2) + pow(Y_MC_Stat_Err/Yield_MC,2) );

				pXS_MC2[Count2] = xs2->gGet_XS_Born(E0,Ep,Theta);
				//pXS_MC2[Count2] = xs2->gGet_XS_Born_ByKin(E0,Ep/1000.0,Theta);
			//	cerr << Form("   --Xbj = %f, XS_EX = %e, XS_MC=%e ", xbj, XS, pXS_MC2[Count2] ) <<endl;

				if(Min_Yield>=Yield_MC&&Yield_MC>1e3)
					Min_Yield = Yield_MC;
				if(Max_Yield<=Yield_MC)
					Max_Yield = Yield_MC;
				if(Min_Yield>=Yield_EX&&Yield_EX>1e3)
					Min_Yield = Yield_EX;
				if(Max_Yield<=Yield_EX)
					Max_Yield = Yield_EX;
				if(Min>=XS)
					Min = XS;	
				if(Max<=XS)
					Max = XS;
				if(Min_X>=xbj)
					Min_X = xbj;	
				if(Max_X<=xbj)
					Max_X = xbj;

				if(Min>= pXS_MC2[Count2])
					Min =  pXS_MC2[Count2];	
				if(Max<= pXS_MC2[Count2])
					Max =  pXS_MC2[Count2];

				if(Min_R>=pY_R2[Count2])
					Min_R = pY_R2[Count2];
				if(Max_R<=pY_R2[Count2])
					Max_R = pY_R2[Count2];

				Count2++;
			}
			if ( !run_2.good() )
				break;
		}
		run_2.close();
		delete xs2;
		cerr << "  Total XS Points for 2nd  = " << Count2 <<endl;
	}
	/*}}}*/

	/*Third{{{*/
	Bool_t bMore1 = kTRUE;
	TString infile3 = aFileName3;
//		if(infile3 =="x")
//			bMore1 = kFALSE;
	TString Arm3="X";
	if(infile3.Contains("L_"))
		Arm3="L";
	else if(infile3.Contains("R_"))
		Arm3="R";

	Int_t Count3=0;
	TString Kin_Name3; 


	if(bMore1){
	Kin = gGet_Kin_Name(infile3.Data());

	if(Kin=="MM"){
		cerr<<"3rd: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
	}
	if(Kin=="3.1"||Kin=="3.2")
		Theta = 21.00; 
	else if(Kin=="4.1"||Kin=="4.2")
		Theta = 23.00;
	else if(Kin=="5.0"||Kin=="5.05"||Kin=="5.1"||Kin=="5.2")
		Theta =  25.00;
	else if(Kin=="6.5")
		Theta = 28.00;
	else
		cerr<<"*** ERROR, unknown kinematics setting!"<<endl;

	 Kin_Name3 = Form("Kin%s",Kin.Data());

		ifstream run_3; run_3.open(infile3);

		// Target = gGet_Target_Name(infile3.Data());

		cerr<<"==== Reading 3rd file from "<<infile3<<endl;

		Get_XS* xs3 = new Get_XS();
		xs3->Load_Table(Target.Data(),Kin_Name3.Data());
		//xs3->Load_Table_ByKin(Target.Data(),Kin_Name3.Data());

		comment.ReadLine(run_3);
		while ( run_3>>XS>>XS_Stat_Err>>XS_Sys_Err>>xbj>>angle>>Ep>>nu>>Q2>>Ei>>p>>Livetime>>Ntg>>Ni>>Nf_EX>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Sys_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Sys_Err )
		{
			if ( angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Sys_Err,2)+pow(XS_Stat_Err,2))/XS <0.2)
			{
				pXS3[Count3] = XS;      pXS_Err3[Count3] = XS_Stat_Err;
				pXbj3[Count3] = xbj;    pXbj_Err3[Count3] = 0.0;

				pYield_MC3[Count3]=Yield_MC; 
				pYield_EX3[Count3]=Yield_EX;
				pYield_MC_Err3[Count3]=Y_MC_Stat_Err; 
				pYield_EX_Err3[Count3]=Y_EX_Stat_Err;
				pY_R3[Count3]=Yield_EX/Yield_MC;
				pY_R_Err3[Count3]=pY_R3[Count3] * sqrt( pow(Y_EX_Stat_Err/Yield_EX,2) + pow(Y_MC_Stat_Err/Yield_MC,2) );

				pXS_MC3[Count3] = xs3->gGet_XS_Born(E0,Ep,Theta);
				//pXS_MC3[Count3] = xs3->gGet_XS_Born_ByKin(E0,Ep/1000.0,Theta);

			//	cerr << Form("   --Xbj = %f, XS_EX = %e, XS_MC=%e ", xbj, XS, pXS_MC3[Count3] ) <<endl;
				if(Min_Yield>=Yield_MC&&Yield_MC>=1e3)
					Min_Yield = Yield_MC;
				if(Max_Yield<=Yield_MC)
					Max_Yield = Yield_MC;
				if(Min_Yield>=Yield_EX&&Yield_EX>=1e3)
					Min_Yield = Yield_EX;
				if(Max_Yield<=Yield_EX)
					Max_Yield = Yield_EX;

				if(Min_X>=xbj)
					Min_X = xbj;	
				if(Max_X<=xbj)
					Max_X = xbj;

				if(Min>=XS)
					Min = XS;	
				if(Max<=XS)
					Max = XS;
				if(Min>= pXS_MC3[Count3])
					Min =  pXS_MC1[Count3];	
				if(Max<= pXS_MC3[Count3])
					Max =  pXS_MC3[Count3];

				if(Min_R>=pY_R3[Count3])
					Min_R = pY_R3[Count3];
				if(Max_R<=pY_R3[Count3])
					Max_R = pY_R3[Count3];

				Count3++;
			}
			if ( !run_3.good() )
				break;
		}
		run_3.close();
		delete xs3;
		cerr << "  Total XS Points for 3rd = " << Count3 <<endl;
	}
	/*}}}*/

	/*Forth{{{*/
	TString Kin_Name4 ="";
	Bool_t bMore2= kTRUE;

	TString infile4 = aFileName4;
	cerr<<"==== Reading 4th file from "<<infile4<<endl;
	TString Arm4="X";
	if(infile4 =="x")
		bMore2= kFALSE;
	if(infile4.Contains("L_"))
		Arm4="L";
	else if(infile4.Contains("R_"))
		Arm4="R";

	Int_t Count4=0;
	if(bMore2){
		ifstream run_4; run_4.open(infile4);
		//	Target = gGet_Target_Name(infile4.Data());
		Kin = gGet_Kin_Name(infile4.Data());
		if(Kin=="MM"){
			cerr<<"4th: Kin (3.1,3.2,4.1,4.2,5.0,5.05,5.1,5.2,6.5) = "; cin >> Kin;
		}
		if(Kin=="3.1"||Kin=="3.2")
			Theta = 21.00;
		else if(Kin=="4.1"||Kin=="4.2")
			Theta = 23.00;
		else if(Kin=="5.0"||Kin=="5.05"||Kin=="5.1"||Kin=="5.2")
			Theta =  25.00;
		else if(Kin=="6.5")
			Theta = 28.00;
		else
			cerr<<"*** ERROR, unknown kinematics setting!"<<endl;
		Kin_Name4 = Form("Kin%s",Kin.Data());
		Get_XS* xs4 = new Get_XS();
		xs4->Load_Table(Target.Data(),Kin_Name4.Data());
		//xs4->Load_Table_ByKin(Target.Data(),Kin_Name4.Data());
		comment.ReadLine(run_4);
		while ( run_4>>XS>>XS_Stat_Err>>XS_Sys_Err>>xbj>>angle>>Ep>>nu>>Q2>>Ei>>p>>Livetime>>Ntg>>Ni>>Nf_EX>>Nf_SAMC>>Nf_SAMC_Gen>>Yield_EX>>Y_EX_Stat_Err>>Y_EX_Sys_Err>>Yield_MC>>Y_MC_Stat_Err>>Y_MC_Sys_Err )
		{

			//		if(XS_Stat_Err<0.0){
			//		  Y_EX_Stat_Err = Yield_EX * sqrt(1./Nf_EX+1./Ni);
			//		  XS_Stat_Err = XS * sqrt( pow(Y_EX_Stat_Err/Yield_EX,2)+pow(Y_MC_Stat_Err/Yield_MC,2));
			//		}
			//			XS*=1e33; XS_Stat_Err*=1e33;  XS_Sys_Err *= 1e33; //From cm^2/MeV/sr to nb/MeV/sr
			//            Yield_EX*=1e33; Y_EX_Stat_Err*=1e33; Y_EX_Sys_Err*=1e33;
			if ( angle<180 &&xbj>0.5  && XS>0.0 && sqrt(pow(XS_Sys_Err,2)+pow(XS_Stat_Err,2))/XS <0.2)
			{
				pXS4[Count4] = XS;      pXS_Err4[Count4] = XS_Stat_Err;
				pXbj4[Count4] = xbj;    pXbj_Err4[Count4] = 0.0;
				pYield_MC4[Count4]=Yield_MC; 
				pYield_EX4[Count4]=Yield_EX;
				pYield_MC_Err4[Count4]=Y_MC_Stat_Err; 
				pYield_EX_Err4[Count4]=Y_EX_Stat_Err;
				pY_R4[Count4]=Yield_EX/Yield_MC;
				pY_R_Err4[Count4]=pY_R4[Count4] * sqrt( pow(Y_EX_Stat_Err/Yield_EX,2) + pow(Y_MC_Stat_Err/Yield_MC,2) );

				pXS_MC4[Count4] = xs4->gGet_XS_Born(E0,Ep,Theta);
				//pXS_MC4[Count4] = xs4->gGet_XS_Born_ByKin(E0,Ep/1000.0,Theta);
			//	cerr << Form("   --Xbj = %f, XS_EX = %e, XS_MC=%e ", xbj, XS, pXS_MC4[Count4] ) <<endl;

				if(Min_Yield>=Yield_MC&&Yield_MC>1e3)
					Min_Yield = Yield_MC;
				if(Max_Yield<=Yield_MC)
					Max_Yield = Yield_MC;
				if(Min_Yield>=Yield_EX&&Yield_EX>1e3)
					Min_Yield = Yield_EX;
				if(Max_Yield<=Yield_EX)
					Max_Yield = Yield_EX;
				if(Min>=XS)
					Min = XS;	
				if(Max<=XS)
					Max = XS;
				if(Min_X>=xbj)
					Min_X = xbj;	
				if(Max_X<=xbj)
					Max_X = xbj;

				if(Min>= pXS_MC4[Count4])
					Min =  pXS_MC4[Count4];	
				if(Max<= pXS_MC4[Count4])
					Max =  pXS_MC4[Count4];

				if(Min_R>=pY_R4[Count4])
					Min_R = pY_R4[Count4];
				if(Max_R<=pY_R4[Count4])
					Max_R = pY_R4[Count4];

				Count4++;
			}
			if ( !run_4.good() )
				break;
		}
		run_4.close();
		delete xs4;
		cerr << "  Total XS Points for 4th  = " << Count4 <<endl;
	}
	/*}}}*/

}
/*}}}*/


int main(int argc, char** argv){



	int err = getargs(argc,argv);

	if(err>=0){
		aFileName1 = gFile1;
		aFileName2 = gFile2;
		aFileName3 = gFile3;
		aFileName4 = gFile4;
		Target = gTgt;
		Yield_Plot(); 
	}
	else
		cerr<<"*** ERROR, I can not recoginize the parameters!"<<endl;

	return 0;
}

/*int getargs(int argc,char** argv){{{*/
int getargs(int argc,char** argv)
{
	char* argptr;
	bool noStop;  
	int err=-1;

	for(int i=0;i<argc;i++){
		argptr = argv[i];
		if(*argptr=='-'){
			argptr++;
			switch (*argptr){
				case '1':
					if(*(++argptr))
						gFile1 = argptr;
					err=0;
					break;
				case '2':
					if(*(++argptr))
						gFile2 = argptr;
					err=0;
					break;
				case '3':
					if(*(++argptr))
						gFile3 = argptr;
					err=0;
					break;
				case '4':
					if(*(++argptr))
						gFile4 = argptr;
					err=0;
					break;
				case 'T':
					if(*(++argptr))
						gTgt = argptr;
					err=0;
					break;
				case 'h':
					cerr <<"================================================"<<endl;
					cerr <<"Option: " <<endl;
					cerr <<"-N[*.dat] Input File,N=1,2,3,4, *.dat =x for nothing" <<endl;
					cerr <<"-T[H2,He3,He4,C12,Ca40,Ca48] Target Name" <<endl;
					cerr <<endl<<"================================================"<<endl;
					noStop=false;
					err=-1;
					goto OUT;
					break;
				default:
					cerr <<"================================================"<<endl;
					cerr <<"Option: " <<endl;
					cerr <<"-N[*.dat] Input File,N=1,2,3,4, *.dat =x for nothing" <<endl;
					cerr <<"-T[H2,He3,He4,C12,Ca40,Ca48] Target Name" <<endl;
					cerr <<endl<<"================================================"<<endl;
					err=-1;
					break;
			}

		}
		noStop=true;
OUT:if(!noStop){break;}
	continue;
	}
	return err; 
}
/*}}}*/		
