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
//#include "/w/halla-2/e08014/yez/Cross_Section/SRC/XGT2_Main.h"
#include "./XGT2_Main.h"
#include "/w/halla-2/e08014/yez/Cross_Section/SRC/XGT2_XEMC.h"

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

int getargs(int argc,char** argv);
char* gInfile;
char* gTgt;
TString infilename; 
TString Target;

void Change(){
   ifstream infile(infilename);

  TString file;
  TString file1; 
  TString Kin,Arm;
  while(!infile.eof()){
    infile >> file;
    Kin = gGet_Kin_Name(file.Data());
    if(file.Contains("L"))
	   Arm="L";
    else if(file.Contains("R"))
	   Arm="R";
    else
		Arm="X";

	file1 = Form("%s_Kin%s_%s.dat",Arm.Data(),Kin.Data(),Target.Data());
    cerr<<Form(" Changing File Name from -%s- to -%s-",file.Data(),file1.Data())<<endl;
    gSystem->Exec(Form("cp -p %s %s", file.Data(), file1.Data())) ;
  }

}
/*int main{{{*/
int main(int argc, char**argv){
	int pserr = getargs(argc,argv);
	if(pserr<0){
		outlog<<"****** I can not recognize the parameters!"<<endl;
		cerr<<"****** I can not recognize the parameters!"<<endl;
		return -1;
	}
    else{
		infilename = gInfile;
		Target=gTgt;
		Change();
	}
}
/*}}}*/
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
				case 'I':
					if(*(++argptr))
						gInfile = argptr;
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
					cerr <<"-I Input File" <<endl;
					cerr <<"-T Target"<<endl;
					cerr <<endl<<"================================================"<<endl;
					noStop=false;
					err=-1;
					goto OUT;
					break;
				default:
					cerr <<"================================================"<<endl;
					cerr <<"Option: " <<endl;
					cerr <<"-I[xs_c12_kin3.1.dat] Input File" <<endl;
					cerr <<"-L[c12_kin3.1.log] Log File"<<endl;
					cerr <<"-C[Dp0.04] Comment, such as Dp=4%"<<endl;
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
