/*C/C++ Includes{{{*/
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
/*}}}*/
/*ROOT Includes{{{*/ #include <TSystem.h>
#include <TString.h>
#include <TStyle.h>
#include <Riostream.h>
#include "TObjString.h"
#include <TNamed.h>
#include <TPRegexp.h>
#include <TObjArray.h>
#include <TChain.h>
#include <TMath.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TROOT.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TDatime.h>
#include <TError.h>
#include <TVirtualFitter.h>
#include <TSQLServer.h>
#include <TSQLResult.h>
#include <TSQLRow.h>
#include <TCut.h>
#include <TMultiGraph.h>
#include <TCutG.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TLegend.h>
#include <TRandom3.h>
//#include <TMatrix.h>
/*}}}*/

using namespace::std;
using namespace::TMath;
const TString XGT2_DIR = "/work/halla/e08014/disk1/yez/Xbj_Cross_Section/";

/*inline vector<TString> Tokens(TString aline,TString aDelim=" "){{{*/
inline vector<TString> Tokens(TString aline,TString aDelim=" ")
{
    Int_t i;
    TObjArray* InObjArray;
    TObjString* os;
    TString s;
    vector<TString> OutStringVec;
    OutStringVec.clear();

    InObjArray=aline.Tokenize(aDelim);
    for ( i=0; i<InObjArray->GetEntriesFast(); i++ )
    {
        os=(TObjString*)InObjArray->At(i);
        s=os->GetString();
        OutStringVec.push_back(s);
    }
    return OutStringVec;
}
/*}}}*/

/*inline vector<Int_t> gGet_RunNoChain(const Int_t& aRunNo,const TString& aString){{{*/
inline vector<Int_t> gGet_RunNoChain(const Int_t& aRunNo,const TString& aString)
{
    vector<Int_t> output;
    if(aRunNo>1000&aRunNo<4300)
        output.push_back(aRunNo);
    vector<TString> input=Tokens(aString);
    unsigned int i;
    for ( i=0; i<input.size(); i++ )
    {
        if ( isdigit(*input[i].Data()) || input[i].BeginsWith("-") )
        {
            vector<TString> tmp=Tokens(input[i],'-');
            if ( tmp.size()<=2 )
            {
                // Int_t FirstRunNo;
                Int_t LastRunNo;
                Int_t thisrunno;
                size_t index=input[i].First('-');
                if ( index==0 )
                {
                    thisrunno=aRunNo;
                    LastRunNo=tmp[0].Atoi();
                }
                else if ( index<input[i].Length() )
                {
                    thisrunno=tmp[0].Atoi();
                    LastRunNo=tmp[1].Atoi();
                }
                else
                {
                    thisrunno=tmp[0].Atoi();
                    LastRunNo=thisrunno;
                }
                if ( thisrunno>LastRunNo )
                {
                    thisrunno ^= LastRunNo;
                    LastRunNo ^= thisrunno;
                    thisrunno ^= LastRunNo;
                }
                while ( thisrunno<=LastRunNo )
                {
                    if ( thisrunno!=aRunNo )
                        output.push_back(thisrunno);
                    thisrunno++;
                }
            }
        }
    }
    for ( i=0; i<output.size(); i++ )
    {
        if ( i==0 && output.size()>1 ){
            cerr<<"      RunNoChain is "<<output[i];
        }
        else if ( i==0 && i==(output.size()-1) ){
            cerr<<"      RunNoChain is "<<output[i]<<endl;
        }
        else if ( i==(output.size()-1) ){
            cerr<<" "<<output[i]<<endl;
        }
        else{
            cerr<<" "<<output[i];
        }
    }
    return output;
}
/*}}}*/

/*inline TString gGet_InputFile_Var(const TString& aFile_Name,const Int_t& aLine){{{*/
inline TString gGet_InputFile_Var(const TString& aFile_Name,const Int_t& aLine)
{
    ifstream file(aFile_Name.Data());
    TString content;
    Int_t i=0;
    TString outstring;
    while ( content.ReadLine(file) )
    {
        if ( i==aLine )
        {
            outstring=content;
            break;
        }
        i++;
        if ( !file.good() )
            break;
    }
    file.close();
    if ( outstring=="\"\"" )
        outstring="";
    return outstring;
}
/*}}}*/

char* gTarget1, *gTarget2, *gKin, *gCom;
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
                case 'U':
                    if(*(++argptr))
                        gTarget1 = argptr;
                    err=0;
                    break; 
                case 'D':
                    if(*(++argptr))
                        gTarget2 = argptr;
                    err=0;
                    break;
                case 'K':
                    if(*(++argptr))
                        gKin = argptr;
                    err=0;
                    break;
                case 'C':
                    if(*(++argptr))
                        gCom = argptr;
                    err=0;
                    break;
                case 'h':
                    cerr <<"================================================"<<endl;
                    cerr <<"Option: " <<endl;
                    cerr <<"-U[He3,He4,C12,Ca40,Ca48] Target" <<endl;
                    cerr <<"-D[He3,He4,C12,Ca40,Ca48] Target" <<endl;
                    cerr <<"-K[3.1,3.2] Kinematic"<<endl;
                    cerr <<"-C[DpTh40] Comment, such as Dp=4%"<<endl;
                    cerr <<endl<<"================================================"<<endl;
                    noStop=false;
                    err=-1;
                    goto OUT;
                    break;
                default:
                    cerr <<"================================================"<<endl;
                    cerr <<"Option: " <<endl;
                    cerr <<"-U[He3,He4,C12,Ca40,Ca48] Target" <<endl;
                    cerr <<"-D[He3,He4,C12,Ca40,Ca48] Target" <<endl;
                    cerr <<"-K[3.1,3.2] Kinematic"<<endl;
                    cerr <<"-C[DpTh40] Comment, such as Dp=4%"<<endl;
                    cerr <<endl<<"================================================"<<endl;
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

int main(int argc,char** argv){

    int pserr = getargs(argc,argv);

    TString Target1= gTarget1;
    TString Target2= gTarget2;
    TString aKin = gKin; TString Kin = Form("Kin%s",aKin.Data());
    TString Com = gCom;


    vector<double> vXS_EX1L,vXS_Err1L, vXS_MC1L, vXbj1L;
    vector<double> vXS_EX1R,vXS_Err1R, vXS_MC1R, vXbj1R;
    vector<double> vXS_EX2L,vXS_Err2L, vXS_MC2L, vXbj2L;
    vector<double> vXS_EX2R,vXS_Err2R, vXS_MC2R, vXbj2R;
    double xs_mc, xbj, xs_ex, xs_err1, xs_err2;
    TString InputFilePath1 = Form("%sresults/%s/%s/", XGT2_DIR.Data(),Target1.Data(),Com.Data());
    TString InputFilePath2 = Form("%sresults/%s/%s/", XGT2_DIR.Data(),Target2.Data(),Com.Data());

    /*Target1{{{*/
    TString InputDataName1L= Form("%s/results/%s/%s/L_%s_%s_Yield.dat_%s",
            XGT2_DIR.Data(),Target1.Data(),Com.Data(),Kin.Data(),Target1.Data(),Com.Data());

    if(!(gSystem->FindFile(InputFilePath1.Data(), InputDataName1L))){
        cerr<<" *** RootFile doesn't exist--> "<<InputDataName1L.Data()<<endl;
        return -1;
    }

    cerr<<" &&& Reading in DataFile --> "<<InputDataName1L.Data()<<endl;
    ifstream run_1L(InputDataName1L.Data());

    double dummy;
    TString com;
    com.ReadLine(run_1L);
    while ( run_1L>>xs_ex>>xs_err1>>xs_err2>>xs_mc >> xbj
            >>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy
                 >>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy){

        cout<<Form("--- From 1L: xbj=%f,  XS_EX=%e", xbj, xs_ex)<<endl;

        vXbj1L.push_back(xbj);
        vXS_EX1L.push_back(xs_ex);
        vXS_Err1L.push_back(sqrt(xs_err1*xs_err1+xs_err2*xs_err2));
        vXS_MC1L.push_back(xs_mc);
    }
    run_1L.close();

    TString InputDataName1R= Form("%s/results/%s/%s/R_%s_%s_Yield.dat_%s",
            XGT2_DIR.Data(),Target1.Data(),Com.Data(),Kin.Data(),Target1.Data(),Com.Data());
    cerr<<" &&& Reading in DataFile --> "<<InputDataName1R.Data()<<endl;

    if(!(gSystem->FindFile(InputFilePath1.Data(), InputDataName1R))){
        cerr<<" *** RootFile doesn't exist--> "<<InputDataName1R.Data()<<endl;
        return -1;
    }

    ifstream run_1R(InputDataName1R.Data());

    com.ReadLine(run_1R);
    while ( run_1R>>xs_ex>>xs_err1>>xs_err2>>xs_mc >> xbj
            >>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy
                 >>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy){

        cout<<Form("--- From 1R: xbj=%f,  XS_EX=%e", xbj, xs_ex)<<endl;

        vXbj1R.push_back(xbj);
        vXS_EX1R.push_back(xs_ex);
        vXS_Err1R.push_back(sqrt(xs_err1*xs_err1+xs_err2*xs_err2));
        vXS_MC1R.push_back(xs_mc);
    }
    run_1R.close();
    /*}}}*/
    
    /*Target2{{{*/
    TString InputDataName2L= Form("%s/results/%s/%s/L_%s_%s_Yield.dat_%s",
            XGT2_DIR.Data(),Target2.Data(),Com.Data(),Kin.Data(),Target2.Data(),Com.Data());

    if(!(gSystem->FindFile(InputFilePath2.Data(), InputDataName2L))){
        cerr<<" *** RootFile doesn't exist--> "<<InputDataName2L.Data()<<endl;
        return -1;
    }
    cerr<<" &&& Reading in DataFile --> "<<InputDataName2L.Data()<<endl;
    ifstream run_2L(InputDataName2L.Data());

    com.ReadLine(run_2L);
    while ( run_2L>>xs_ex>>xs_err1>>xs_err2>>xs_mc >> xbj
            >>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy
                 >>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy){

        cout<<Form("--- From 2L: xbj=%f,  XS_EX=%e", xbj, xs_ex)<<endl;

        vXbj2L.push_back(xbj);
        vXS_EX2L.push_back(xs_ex);
        vXS_Err2L.push_back(sqrt(xs_err1*xs_err1+xs_err2*xs_err2));
        vXS_MC2L.push_back(xs_mc);
    }
    run_2L.close();

    TString InputDataName2R= Form("%s/results/%s/%s/R_%s_%s_Yield.dat_%s",
            XGT2_DIR.Data(),Target2.Data(),Com.Data(),Kin.Data(),Target2.Data(),Com.Data());

    if(!(gSystem->FindFile(InputFilePath2.Data(), InputDataName2R))){
        cerr<<" *** RootFile doesn't exist--> "<<InputDataName2R.Data()<<endl;
        return -1;
    }

    cerr<<" &&& Reading in DataFile --> "<<InputDataName2R.Data()<<endl;
    ifstream run_2R(InputDataName2R.Data());

    com.ReadLine(run_2R);
    while ( run_2R>>xs_ex>>xs_err1>>xs_err2>>xs_mc >> xbj
            >>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy
                 >>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy){

        cout<<Form("--- From 2R: xbj=%f,  XS_EX=%e", xbj, xs_ex)<<endl;

        vXbj2R.push_back(xbj);
        vXS_EX2R.push_back(xs_ex);
        vXS_Err2R.push_back(sqrt(xs_err1*xs_err1+xs_err2*xs_err2));
        vXS_MC2R.push_back(xs_mc);
    }
    run_2R.close();
    /*}}}*/
    

    const int NL_Evt = vXbj1L.size()>vXbj2L.size()?vXbj1L.size():vXbj2L.size();
    const int NR_Evt = vXbj1R.size()>vXbj2R.size()?vXbj1R.size():vXbj2R.size();

    double Xbj_L[NL_Evt], XS_L[NL_Evt], XS_L_Err[NL_Evt];
    double Xbj_R[NR_Evt], XS_R[NR_Evt], XS_R_Err[NR_Evt];
    double  xbj_Max = -1000.0, xbj_Min = 1000.0;
    double Y_Min =1000., Y_Max = -1000.;

    int kL=0;
    for(int i =0;i<vXbj1L.size();i++){
        for(int j=0;j<vXbj2L.size();j++){
            if(fabs(vXbj2L[j]-vXbj1L[i])<0.0001){
                if(vXS_EX2L[j]>1e-30){
                    Xbj_L[kL] = vXbj1L[i];
                    XS_L[kL] = vXS_EX1L[i] / vXS_EX2L[j];
                    XS_L_Err[kL] = XS_L[kL]*sqrt( pow(vXS_Err1L[i]/vXS_EX1L[i],2) + pow(vXS_Err2L[j]/vXS_EX2L[j],2) );
                    
                    xbj_Max = Xbj_L[kL]>xbj_Max?Xbj_L[kL]:xbj_Max;
                    xbj_Min = Xbj_L[kL]<xbj_Min?Xbj_L[kL]:xbj_Min;
                    Y_Max = XS_L[kL]+XS_L_Err[kL]>Y_Max?XS_L[kL]+XS_L_Err[kL]:Y_Max;
                    Y_Min = XS_L[kL]-XS_L_Err[kL]<Y_Min?XS_L[kL]-XS_L_Err[kL]:Y_Min;

      
                    cout<<Form("-L- xbj=%4.3f, XS_L=%5.3f", Xbj_L[kL], XS_L[kL])<<endl;
                    kL++;
                }
            }
        }
    }
    const int N_L = kL--;

    int kR=0;
    for(int i =0;i<vXbj1R.size();i++){
        for(int j=0;j<vXbj2R.size();j++){
            if(fabs(vXbj2R[j]-vXbj1R[i])<0.0001){
                if(vXS_EX2R[j]>1e-30){
                    Xbj_R[kR] = vXbj1R[i];
                    XS_R[kR] = vXS_EX1R[i] / vXS_EX2R[j];
                    XS_R_Err[kR] = XS_R[kR]*sqrt( pow(vXS_Err1R[i]/vXS_EX1R[i],2) + pow(vXS_Err2R[j]/vXS_EX2R[j],2) );
                    
                    xbj_Max = Xbj_R[kR]>xbj_Max?Xbj_R[kR]:xbj_Max;
                    xbj_Min = Xbj_R[kR]<xbj_Min?Xbj_R[kR]:xbj_Min;

                    Y_Max = XS_R[kR]+XS_R_Err[kR]>Y_Max?XS_R[kR]+XS_R_Err[kR]:Y_Max;
                    Y_Min = XS_R[kR]-XS_R_Err[kR]<Y_Min?XS_R[kR]-XS_R_Err[kR]:Y_Min;

                    cout<<Form("-R- xbj=%4.3f, XS_R=%5.3f", Xbj_R[kR], XS_R[kR])<<endl;
                    
                    kR++;
                }
            }
        }
    }
    const int N_R = kR--;

    /*XS  Ratio{{{*/
    TCanvas *c3 = new TCanvas("c3","c3",1200,800);
    gPad->SetGrid();
    TH2F* r = new TH2F("r","",1000,xbj_Min-0.2,xbj_Max+0.2,1000,Y_Min-0.2, Y_Max+0.2);
    r->SetStats(kFALSE);
    r->SetXTitle("X");
    r->GetXaxis()->CenterTitle(1);
    r->GetXaxis()->SetTitleFont(32);
    r->GetXaxis()->SetTitleSize(0.06);
    r->GetXaxis()->SetTitleOffset(0.7);
    r->SetYTitle(Form("#sigma_{%s}/#sigma_{%s}",Target1.Data(),Target2.Data()));
    r->GetYaxis()->CenterTitle(1);
    r->GetYaxis()->SetTitleFont(32);
    r->GetYaxis()->SetTitleSize(0.05);
    r->GetYaxis()->SetTitleOffset(0.7);
    r->Draw(); 

    TGraphErrors *pl_L = new TGraphErrors(N_L,Xbj_L,XS_L,0,XS_L_Err);
    pl_L-> SetMarkerSize(1.5);
    pl_L-> SetMarkerColor(2);
    pl_L-> SetMarkerStyle(22);
    pl_L->Draw("p");

    TGraphErrors *pl_R = new TGraphErrors(N_R,Xbj_R,XS_R,0,XS_R_Err);
    pl_R-> SetMarkerSize(1.5);
    pl_R-> SetMarkerColor(4);
    pl_R-> SetMarkerStyle(23);
    pl_R->Draw("p");

    TLegend *l3 = new TLegend(0.15,0.70,0.40, 0.80,Form("%s/%s XS Ratio",Target1.Data(),Target2.Data()));
    l3->SetBorderSize(0);
    l3->SetTextSize(0.025);
    l3->SetTextFont(22);

    l3->AddEntry(pl_L, Form(" %s (HRS-L)",Kin.Data()),"p");
    l3->AddEntry(pl_R, Form(" %s (HRS-R)",Kin.Data()),"p");
    l3->Draw();
    /*}}}*/

    c3->Print(Form("%s_%s_LR_%s_%s.pdf",Target1.Data(),Target2.Data(),Kin.Data(),Com.Data()));
    c3->Print(Form("%s_%s_LR_%s_%s.png",Target1.Data(),Target2.Data(),Kin.Data(),Com.Data()));

    //	f1->Close();
}
