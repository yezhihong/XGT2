#include "/Users/yez/work/xgt2/Xbj_Cross_Section/SRC/XGT2_Main.h"
#include "/Users/yez/work/xgt2/Xbj_Cross_Section/SRC/XGT2_XEMC.h"
#include "TLegend.h"
#include "TLine.h"
#include "TGraphAsymmErrors.h"

#include "XGT2_Tools.h"
#include "XGT2_Merge.h"
//#include "XGT2_Merge_New.h"

/*Comment{{{*/
/*Format in aFileName:
  Target 1:
  line#1 --> The first  setting of each angle on  L-HRS, like L_Kin3.1 ...
  line#2 --> The second setting of each angle on  L-HRS, like L_Kin3.2 ...
  line#3 --> The first  setting of each angle on  R-HRS, like R_Kin3.1 ...
  line#4 --> The second setting of each angle on  R-HRS, like R_Kin3.2 ...
  Target 2:  
  line#5 --> The first  setting of each angle on  L-HRS, like L_Kin3.1 ...
  line#6 --> The second setting of each angle on  L-HRS, like L_Kin3.2 ...

  line#7 --> The first  setting of each angle on  R-HRS, like R_Kin3.1 ...
  line#8 --> The second setting of each angle on  R-HRS, like R_Kin3.2 ...
  */
/*}}}*/

/*main{{{*/
int main(int argc, char** argv)
{
	/*ROOT Define{{{*/
	// Fill color
	gStyle->SetStatColor(0);
	gStyle->SetTitleFillColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetPadColor(0);
	gStyle->SetFrameFillColor(0);

	// Border mode
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetPalette(1,0);

	// Font
	gStyle->SetTextFont(22);
	gStyle->SetLabelFont(32, "xyz");
	gStyle->SetTitleFont(22, "xyz");
	gStyle->SetStatFont(22);
	gStyle->SetTitleFillColor(0);

	// Opt
	//    gStyle->SetOptDate(0);
	//    gStyle->SetOptTitle(1);
	//    gStyle->SetOptStat(1);
	gStyle->SetOptFit(1);
	//    // Margin
	// //    gStyle->SetPadLeftMargin(0.1);
	// //    gStyle->SetPadRightMargin(0.1);
	// //    gStyle->SetPadTopMargin(0.1);
	// //    gStyle->SetPadBottomMargin(0.1);


	//void HallA_style() {
	gROOT->SetStyle("Plain");
	gStyle->SetPaperSize(TStyle::kUSLetter);
	gStyle->SetPaperSize(18,22);
	gStyle->SetOptFit(1111);
	gStyle->SetPalette(1);
	gStyle->SetNdivisions(505);

	gStyle->SetCanvasColor(0);
	gStyle->SetPadTopMargin(.05);
	gStyle->SetPadLeftMargin(.15);
	gStyle->SetPadRightMargin(.1);
	gStyle->SetPadBottomMargin(.15);
	gStyle->SetTitleYOffset(1.3);
	gStyle->SetLabelFont(32,"X");
	gStyle->SetLabelFont(32,"Y");

	// prepare gStyle to be useful
	//   1 = solid
	//   2 = long dash (30 10)
	gStyle->SetTitleFillColor(-1); 
	//   3 = dotted (4 8)
	//   4 = dash-dot (15 12 4 12)
	//   5 = short dash ( 15 15 )
	//   6 = dash-dot-dot 
	gStyle->SetLineStyleString(1,"[]");
	gStyle->SetLineStyleString(2,"[30 10]");
	gStyle->SetLineStyleString(3,"[4 8]");
	gStyle->SetLineStyleString(4,"[15 12 4 12]");
	gStyle->SetLineStyleString(5,"[15 15]");
	gStyle->SetLineStyleString(6,"[15 12 4 12 4 12]");
	gStyle->SetLabelSize(0.05,"X");
	gStyle->SetLabelSize(0.05,"Y");
	gStyle->SetNdivisions(505,"Y");
	gStyle->SetOptDate(0);
	gStyle->SetDateY(.98);
	gStyle->SetStripDecimals(kFALSE);

	gStyle->SetHistFillColor(0); 
	gStyle->SetFillColor(0); 
	gStyle->SetFillStyle(4000); 
	gStyle->SetStatStyle(0); 
	gStyle->SetTitleStyle(0); 
	gStyle->SetCanvasBorderSize(0); 
	gStyle->SetFrameBorderSize(0); 
	gStyle->SetLegendBorderSize(0); 
	gStyle->SetStatBorderSize(0); 
	gStyle->SetTitleBorderSize(0); 

	/*}}}*/

    //cerr<<" 1 vs 2 (He3 or He4 or C12) for 1 = "; cin >> Target0;
    //cerr<<" 1 vs 2 (H2  or He3 or He4) for 2 = "; cin >> Target;
    //cerr<<" Com for 1 = "; cin >> Com0;
    //cerr<<" Com for 2 = "; cin >> Com;

    if(argc!=4){
    Target0 = argv[1];
    Target = argv[2];
    Com0 = argv[3];
    Com = argv[4];

    OutFile_Dir = Form("./both/%s_%s",Com0.Data(), Com.Data());
    if(!gSystem->OpenDirectory(OutFile_Dir.Data()))
        gSystem->mkdir(OutFile_Dir);	


    }else{
      cerr<<"--- Wrong inputs!!!"<<endl; return -1;
    }

    TString lTarget0 = Get_Target_Label(Target0.Data());
    TString lTarget  = Get_Target_Label(Target.Data());

	gGet_Ep_Edge(Target.Data());//Get Ep Range from Xbj edge, use the lower mass to define xbj, 08/06/2015, ZYE
	int A1 = 0, A2 = 0, Z1 = 0, Z2=0;

	/*Get Target Info 1{{{*/
	if(Target0 == "H2"||Target == "D2"){
		A1 = 2; Z1 = 1;  
	}
	else if(Target0 == "He3"){
		A1 = 3; Z1 = 2;  
	}
	else if(Target0 == "He4"){
		A1 = 4; Z1 = 2; 
	}
	else if(Target0 == "Be"){
		A1 = 9; Z1 = 4; 
	}
	else if(Target0 == "C12"){
		A1 = 12; Z1 = 6; 
	}
	else if(Target0 == "Al"){
		A1 = 27; Z1 = 13; 
	}
	else if(Target0 == "Ca40"){
		A1 = 40; Z1 = 20;
	}
	else if(Target0 == "Ca48"){
		A1 = 48; Z1 = 20; 
	}
	else
		cerr<<" **** ERROR, I don't know the target!!!"<<endl;
	/*}}}*/

    /*Get Target Info 2{{{*/
	if(Target == "H2"||Target == "D2"){
		A2 = 2; Z2 = 1;  
	}
	else if(Target == "He3"){
		A2 = 3; Z2 = 2;  
	}
	else if(Target == "He4"){
		A2 = 4; Z2 = 2; 
	}
	else if(Target == "Be"){
		A2 = 9; Z2 = 4; 
	}
	else if(Target == "C12"){
		A2 = 12; Z2 = 6; 
	}
	else if(Target == "Al"){
		A2 = 27; Z2 = 13; 
	}
	else if(Target == "Ca40"){
		A2 = 40; Z2 = 20;
	}
	else if(Target == "Ca48"){
		A2 = 48; Z2 = 20; 
	}
	else
		cerr<<" **** ERROR, I don't know the target!!!"<<endl;
	/*}}}*/

	/*Get Ratio{{{*/
	bool bMC = kTRUE;
	//bool bMC = kFALSE;
	double Theta =21;
	double Zero[100] = {100*0.0};

	double xbj_21[100], R_EX_21[100], R_EX_Err_21[100], R_MC_21[100];
	int N_21 = 0;
	Merge(Form("./input/R21_%s_%s.rt",Target0.Data(),Target.Data()), xbj_21, R_EX_21, R_EX_Err_21, R_MC_21, &N_21);
	double Q2_21_D = 4.0*E0*Ep_Cut_21_1[0]*pow(TMath::Sin(21.*3.1415926/180.0*0.5),2);
	double Q2_21_U = 4.0*E0*Ep_Cut_21_2[3]*pow(TMath::Sin(21.*3.1415926/180.0*0.5),2);

	double xbj_23[100], R_EX_23[100], R_EX_Err_23[100], R_MC_23[100];
	int N_23 = 0;
	if(!(Target=="H2"))
		Merge(Form("./input/R23_%s_%s.rt",Target0.Data(),Target.Data()), xbj_23, R_EX_23, R_EX_Err_23, R_MC_23, &N_23);
	double Q2_23_D = 4.0*E0*Ep_Cut_23_1[0]*pow(TMath::Sin(23.*3.1415926/180.0*0.5),2);
	double Q2_23_U = 4.0*E0*Ep_Cut_23_2[3]*pow(TMath::Sin(23.*3.1415926/180.0*0.5),2);

	double xbj_QE[100], R_EX_QE[100], R_EX_Err_QE[100], R_MC_QE[100];
	int N_QE = 0;
	if(!(Target=="H2"))
		Merge(Form("./input/RQE_%s_%s.rt",Target0.Data(),Target.Data()), xbj_QE, R_EX_QE, R_EX_Err_QE, R_MC_QE, &N_QE);
	double Q2_25_D = 4.0*E0*Ep_Cut_QE_1[0]*pow(TMath::Sin(25.*3.1415926/180.0*0.5),2);

	double xbj_25[100], R_EX_25[100], R_EX_Err_25[100], R_MC_25[100];
	int N_25 = 0;
	Merge(Form("./input/R25_%s_%s.rt",Target0.Data(),Target.Data()), xbj_25, R_EX_25, R_EX_Err_25, R_MC_25, &N_25);
	double Q2_25_U = 4.0*E0*Ep_Cut_25_2[3]*pow(TMath::Sin(25.*3.1415926/180.0*0.5),2);

	double xbj_25_Total[100], R_EX_25_Total[100], R_EX_Err_25_Total[100], R_MC_25_Total[100];
	int N_25_Total = 0;
	Merge25(Target0.Data(),Target.Data(), xbj_25_Total, R_EX_25_Total, R_EX_Err_25_Total, R_MC_25_Total, &N_25_Total);

	double xbj_2325[100], R_EX_2325[100], R_EX_Err_2325[100], R_MC_2325[100];
	int N_2325 = 0;
	Merge2325(Target0.Data(),Target.Data(), xbj_2325, R_EX_2325, R_EX_Err_2325, R_MC_2325, &N_2325);

	double xbj_212325[100], R_EX_212325[100], R_EX_Err_212325[100], R_MC_212325[100];
	int N_212325 = 0;
	Merge212325(Target0.Data(),Target.Data(), xbj_212325, R_EX_212325, R_EX_Err_212325, R_MC_212325, &N_212325);

	double xbj_28[100], R_EX_28[100], R_EX_Err_28[100], R_MC_28[100];
	int N_28 = 0;
	if(Target0=="C12" && Target=="He3"){
		Merge(Form("./input/R28_%s_%s.rt",Target0.Data(),Target.Data()), xbj_28, R_EX_28, R_EX_Err_28, R_MC_28, &N_28);
	}
	double Q2_28_D = 4.0*E0*Ep_Cut_28_1[0]*pow(TMath::Sin(28.*3.1415926/180.0*0.5),2);
	double Q2_28_U = 4.0*E0*Ep_Cut_28_1[3]*pow(TMath::Sin(28.*3.1415926/180.0*0.5),2);

	//Add E02019 Data
    //
        cout<<"--- Getting E02-019 Data"<<endl;
        double xbj_NF[1000], R_EX_NF[1000], R_EX_Err_NF[1000],R_EX_Err_Up[1000],R_EX_Err_Down[1000];
	//Only fit one angle 18,22,26,32,40,50, 0->for all:
	//if(!(Target0=="C12"&&Target=="He4")){
	int N_NF = 0;  Double_t Theta_NF=18;

	if(Target=="He3" && (Target0=="C12"))
		E02019_A_He3(Target0.Data(), Theta_NF,xbj_NF, R_EX_NF, R_EX_Err_Up,  R_EX_Err_Down, &N_NF);
	if(Target=="He3" && Target0=="He4")
		E02019_He4_He3(Target0.Data(), Theta_NF,xbj_NF, R_EX_NF, R_EX_Err_Up,  R_EX_Err_Down, &N_NF);
        if(Target=="He4" && Target0=="C12")
            E02019_A_He4(Target0.Data(), Theta_NF,xbj_NF, R_EX_NF, R_EX_Err_NF, &N_NF);


	if(0){
		Theta_NF = 18; //0->all
		E02019(Form("./input/RNF_%s_%s.rt",Target0.Data(),Target.Data()), Theta_NF,xbj_NF, R_EX_NF, R_EX_Err_NF, &N_NF);
		Theta_NF = 22; //0->all
		E02019(Form("./input/RNF_%s_%s.rt",Target0.Data(),Target.Data()), Theta_NF,xbj_NF, R_EX_NF, R_EX_Err_NF, &N_NF);
		Theta_NF = 26; //0->all
		E02019(Form("./input/RNF_%s_%s.rt",Target0.Data(),Target.Data()), Theta_NF,xbj_NF, R_EX_NF, R_EX_Err_NF, &N_NF);
	}
	cerr<<Form("@@@@@@@@@@ N_21 = %d, N_23 = %d, N_25 = %d, N_QE = %d, N_28 = %d, N_NF = %d", N_21,N_23,N_25,N_QE,N_28,N_NF)<<endl;

	//Add CLAS Data
	double xbj_CS[1000], R_EX_CS[1000], R_EX_Err_CS[1000];
	int N_CS = 0;  
	if(Target=="He3" && Target0=="He4")
		CLAS_He4_He3( xbj_CS, R_EX_CS, R_EX_Err_CS, &N_CS);
	cerr<<Form("@@@@@@@@@@ N_CLAS = %d", N_CS)<<endl;
	/*}}}*/

	/*Save Ratio Values into files{{{*/
	/*    ofstream outf_21(Form("Ratio_21_%s_%s_%s_%s.dat", Target0.Data(),Target.Data(),Com0.Data(),Com.Data() ));
		  for(int i = 0;i<N_21;i++)
		  outf_21 <<Form("%5d %10.8f, %12.8f, %12.8f",21, xbj_21[i], R_EX_21[i],R_EX_Err_21[i])<<endl;
		  outf_21.close();

		  if(!(Target=="H2")){
		  ofstream outf_23(Form("Ratio_23_%s_%s_%s_%s.dat", Target0.Data(),Target.Data(),Com0.Data(),Com.Data() ));
		  for(int i = 0;i<N_23;i++)
		  outf_23 <<Form("%5d %10.8f, %12.8f, %12.8f",23, xbj_23[i], R_EX_23[i],R_EX_Err_23[i])<<endl;
		  outf_23.close();
		  }

		  ofstream outf_25(Form("Ratio_25_%s_%s_%s_%s.dat", Target0.Data(),Target.Data(),Com0.Data(),Com.Data() ));
		  if(!(Target=="H2")){
		  for(int i = 0;i<N_QE;i++)
		  outf_25 <<Form("%5d %10.8f, %12.8f, %12.8f",25, xbj_QE[i], R_EX_QE[i],R_EX_Err_QE[i])<<endl;
		  }
		  for(int i = 0;i<N_25;i++)
		  outf_25 <<Form("%5d %10.8f, %12.8f, %12.8f",25, xbj_25[i], R_EX_25[i],R_EX_Err_25[i])<<endl;
		  outf_25.close();

		  if(Target0=="C12"&&Target=="He3"){
		  ofstream outf_28(Form("Ratio_28_%s_%s_%s_%s.dat", Target0.Data(),Target.Data(),Com0.Data(),Com.Data() ));
		  for(int i = 0;i<N_28;i++)
		  outf_28 <<Form("%5d %10.8f, %12.8f, %12.8f",28, xbj_28[i], R_EX_28[i],R_EX_Err_28[i])<<endl;
		  outf_28.close();
		  }
		  */
	/*}}}*/

	/*Plot{{{*/
	cerr<<endl<<"@@@@@@@@ Now starting to make some plots ..."<<endl;

	gStyle->SetOptStat(0);

	double RMAX = -1000,RMIN=0.4;/*{{{*/
	for(int i=0; i<N_21; i++)
		RMAX = RMAX?R_EX_21[i]:RMAX<R_EX_21[i];
	for(int i=0; i<N_23; i++)
		RMAX = RMAX?R_EX_23[i]:RMAX<R_EX_23[i];
	for(int i=0; i<N_25; i++)
		RMAX = RMAX?R_EX_25[i]:RMAX<R_EX_25[i];
	if(Target=="He3"){
		for(int i=0; i<N_28; i++)
			RMAX = RMAX?R_EX_28[i]:RMAX<R_EX_28[i];
	}
	for(int i=0; i<N_21; i++)
		RMAX = RMAX?R_MC_21[i]:RMAX<R_MC_21[i];
	for(int i=0; i<N_23; i++)
		RMAX = RMAX?R_MC_23[i]:RMAX<R_MC_23[i];
	for(int i=0; i<N_25; i++)
		RMAX = RMAX?R_MC_25[i]:RMAX<R_MC_25[i];
	if(Target=="He3"){
		for(int i=0; i<N_28; i++)
			RMAX = RMAX?R_MC_28[i]:RMAX<R_MC_28[i];
	}

	double XMax = 3.2;
	if(Target=="He4")
		XMax=3.2;
	if(Target=="He3")
		XMax=3.2;
	if(Target=="H2")
		XMax=2.2;

	if(Target=="He3" &&Target0=="C12")
		//RMAX = 20.0;
		RMAX = 5.0;
	if(Target=="He3" &&Target0=="He4")
		RMAX = 6.0;
	if(Target=="He4" &&Target0=="C12"){
		RMIN = 0.8; RMAX = 4.5;
	}
	if(Target=="Ca40" &&Target0=="Ca48"){
		RMAX = 1.3; RMIN=0.65;
		//RMAX = 1.25; RMIN=0.75;
	}
	if(Target=="Ca48" &&Target0=="Ca40"){
		RMAX = 1.45; RMIN=0.65;
	}
	if(Target=="C12" &&Target0=="Ca40")
		RMAX = 1.5;
	if(Target=="C12" &&Target0=="Ca48")
		RMAX = 1.5;
	if(Target=="H2" &&Target0=="He3")
		RMAX = 3.0;
	if(Target=="H2" &&Target0=="He4")
		RMAX = 5.1;
	if(Target=="H2" &&Target0=="C12"){
		RMIN=0.1; RMAX = 7.5;
	}
	if(Target=="H2" &&Target0=="Ca40"){
		RMIN=0.1; RMAX = 9.5;
	}
	if(Target=="H2" &&Target0=="Ca48"){
		RMIN=0.1; RMAX = 9.5;
	}
	if(Target=="He4" &&Target0=="He3"){
		RMIN=0.0; RMAX = 1.5;
	}
	if(Target=="C12" &&Target0=="He3"){
		RMIN=0.0; RMAX = 1.5;
	}
	if(Target=="C12" &&Target0=="He4"){
		RMIN=0.0; RMAX = 1.5;
	}
        if(Target=="He4" &&Target0=="C12")
		RMAX = 5.0;
	
/*}}}*/


        //RMIN = 0.0;

        TCanvas *c3 = new TCanvas("c3","c3",1200,700);/*{{{*/
        gPad->SetGrid(1);
        c3->cd();
	TH2F *h3 = new TH2F("h3","",300,0.7,XMax,300,RMIN,RMAX);
	h3->SetStats(kFALSE);
	h3->SetXTitle("x");
	h3->GetXaxis()->CenterTitle(1);
	h3->GetXaxis()->SetTitleFont(22);
	h3->GetXaxis()->SetTitleSize(0.08);
	h3->GetXaxis()->SetTitleOffset(0.7);
	//h3->GetYaxis()->SetTitle(Form("#frac{#sigma_{%s}}{#sigma_{%s}} #times #frac{%d}{%d}",lTarget0.Data(),lTarget.Data(),A2,A1));
	//h3->GetYaxis()->SetTitle(Form("#frac{#sigma_{%s}}{%d}/#frac{#sigma_{%s}}{%d}",lTarget0.Data(),A1,lTarget.Data(),A2));
	h3->GetYaxis()->SetTitle(Form("(#sigma_{%s}/%d)/(#sigma_{%s}/%d)",lTarget0.Data(),A1,lTarget.Data(),A2));
	h3->GetYaxis()->CenterTitle(1);
	h3->GetYaxis()->SetTitleFont(22);
	h3->GetYaxis()->SetTitleSize(0.07);
	h3->GetYaxis()->SetTitleOffset(0.6);
	h3->GetYaxis()->CenterTitle();
	gPad->SetLogy(0);
	h3->Draw();

	TCanvas *c31 = new TCanvas("c31","c31",1200,700);
        gPad->SetGrid(1);
	c31->cd();
	TH2F *h31 = new TH2F("h31","",300,0.7,XMax,300,RMIN,RMAX);
	h31->SetStats(kFALSE);
	h31->SetXTitle("x");
	h31->GetXaxis()->CenterTitle(1);
	h31->GetXaxis()->SetTitleFont(22);
	h31->GetXaxis()->SetTitleSize(0.08);
	h31->GetXaxis()->SetTitleOffset(0.7);
	//h31->GetYaxis()->SetTitle(Form("#frac{#sigma_{%s}}{#sigma_{%s}} #times #frac{%d}{%d}",lTarget0.Data(),lTarget.Data(),A2,A1));
    //h31->GetYaxis()->SetTitle(Form("#frac{#sigma_{%s}}{%d}/#frac{#sigma_{%s}}{%d}",lTarget0.Data(),A1,lTarget.Data(),A2));
	h31->GetYaxis()->SetTitle(Form("(#sigma_{%s}/%d)/(#sigma_{%s}/%d)",lTarget0.Data(),A1,lTarget.Data(),A2));
	h31->GetYaxis()->CenterTitle(1);
	h31->GetYaxis()->SetTitleFont(22);
	h31->GetYaxis()->SetTitleSize(0.07);
	h31->GetYaxis()->SetTitleOffset(0.6);
	h31->GetYaxis()->CenterTitle();
	gPad->SetLogy(0);
	h31->Draw();
	TCanvas *c32 = new TCanvas("c32","c32",1200,700);
        gPad->SetGrid(1);
	c32->cd();
	TH2F *h32 = new TH2F("h32","",300,0.7,XMax,300,RMIN,RMAX);
	h32->SetStats(kFALSE);
	h32->SetXTitle("x");
	h32->GetXaxis()->CenterTitle(1);
	h32->GetXaxis()->SetTitleFont(22);
	h32->GetXaxis()->SetTitleSize(0.08);
	h32->GetXaxis()->SetTitleOffset(0.7);
	//h32->GetYaxis()->SetTitle(Form("#frac{#sigma_{%s}}{#sigma_{%s}} #times #frac{%d}{%d}",lTarget0.Data(),lTarget.Data(),A2,A1));
    //h32->GetYaxis()->SetTitle(Form("#frac{#sigma_{%s}}{%d}/#frac{#sigma_{%s}}{%d}",lTarget0.Data(),A1,lTarget.Data(),A2));
	h32->GetYaxis()->SetTitle(Form("(#sigma_{%s}/%d)/(#sigma_{%s}/%d)",lTarget0.Data(),A1,lTarget.Data(),A2));
	h32->GetYaxis()->CenterTitle(1);
	h32->GetYaxis()->SetTitleFont(22);
	h32->GetYaxis()->SetTitleSize(0.07);
	h32->GetYaxis()->SetTitleOffset(0.7);
	h32->GetYaxis()->CenterTitle();
	gPad->SetLogy(0);
	h32->Draw();


	if(Target=="He3" &&Target0=="C12")
		//RMAX = 10.0;
		RMAX = 5.0;
	if(Target=="He3" &&Target0=="He4")
		RMAX = 6.0;
	if(Target=="He4" &&Target0=="C12")
		RMAX = 5.0;
	if(Target=="Ca40" &&Target0=="Ca48"){
		RMIN = 0.8;		RMAX = 1.25;
	}
	if(Target=="C12" &&Target0=="Ca40"){
		RMAX = 1.5; RMIN=0.7;
	}
	if(Target=="C12" &&Target0=="Ca48"){
		RMAX = 1.5; RMIN=0.7;
	}
	if(Target=="H2" &&Target0=="C12"){
		RMIN=0.1;
	}

	TCanvas *c4 = new TCanvas("c4","c4",1200,700);
        gPad->SetGrid(1);
	c4->cd();
	TH2F *h4 = new TH2F("h4","",300,0.7,XMax,300,RMIN,RMAX);
	h4->SetStats(kFALSE);
	h4->SetXTitle("x");
	h4->GetXaxis()->CenterTitle(1);
	h4->GetXaxis()->SetTitleFont(22);
	h4->GetXaxis()->SetTitleSize(0.08);
	h4->GetXaxis()->SetTitleOffset(0.7);
	//h4->GetYaxis()->SetTitle(Form("#frac{#sigma_{%s}}{#sigma_{%s}} #times #frac{%d}{%d}",lTarget0.Data(),lTarget.Data(),A2,A1));
    //h4->GetYaxis()->SetTitle(Form("#frac{#sigma_{%s}}{%d}/#frac{#sigma_{%s}}{%d}",lTarget0.Data(),A1,lTarget.Data(),A2));
	h4->GetYaxis()->SetTitle(Form("(#sigma_{%s}/%d)/(#sigma_{%s}/%d)",lTarget0.Data(),A1,lTarget.Data(),A2));
	h4->GetYaxis()->CenterTitle(1);
	h4->GetYaxis()->SetTitleFont(22);
	h4->GetYaxis()->SetTitleSize(0.07);
	h4->GetYaxis()->SetTitleOffset(0.6);
	h4->GetYaxis()->CenterTitle();
	gPad->SetLogy(0);
	h4->Draw();/*}}}*/

	double lx_min = 0.17, lx_max=0.50;/*{{{*/
	if((Target=="He4" &&Target0=="He3")||(Target=="C12" &&Target0=="He3")||(Target=="C12" &&Target0=="He4")){
		lx_min+=0.3; lx_max+=0.3;
	}
	//TLegend *l1 = new TLegend(lx_min,0.57,lx_max, 0.94,Form("#sigma_{%s} / #sigma_{%s} Ratio: ",lTarget0.Data(),lTarget.Data()));
	TLegend *l1 = new TLegend(lx_min,0.52,lx_max, 0.92,"");
	l1->SetTextSize(0.043);
	l1->SetTextFont(22);
	//TLegend *l11 = new TLegend(lx_min,0.57,lx_max, 0.94,Form("#sigma_{%s} / #sigma_{%s} Ratio: ",lTarget0.Data(),lTarget.Data()));
	TLegend *l11 = new TLegend(lx_min,0.70,lx_max, 0.94,"");
	l11->SetTextSize(0.043);
	l11->SetTextFont(22);

    //TLegend *l12 = new TLegend(lx_min,0.57,lx_max, 0.94,Form("#sigma_{%s} / #sigma_{%s} Ratio: ",lTarget0.Data(),lTarget.Data()));
    TLegend *l12 = new TLegend(lx_min,0.80,lx_max, 0.94,"");
	l12->SetTextSize(0.043);
	l12->SetTextFont(22);

	TGraphErrors *ex21 = new TGraphErrors(N_21,xbj_21, R_EX_21, Zero,R_EX_Err_21);
	ex21->SetMarkerStyle(26);
	ex21->SetMarkerSize(1.5);
	ex21->SetMarkerColor(2);
	ex21->SetLineColor(2);
        ex21->SetLineWidth(1.5);

	TGraphErrors *ex23 = new TGraphErrors(N_23,xbj_23, R_EX_23, Zero,R_EX_Err_23);
	ex23->SetMarkerStyle(25);
	ex23->SetMarkerSize(1.5);
	ex23->SetMarkerColor(4);
	ex23->SetLineColor(4);
    ex23->SetLineWidth(1.5);
  
	TGraphErrors *exQE = new TGraphErrors(N_QE,xbj_QE, R_EX_QE, Zero,R_EX_Err_QE);
	exQE->SetMarkerStyle(24);
	exQE->SetMarkerSize(1.5);
	exQE->SetMarkerColor(1);
	exQE->SetLineColor(1);
    exQE->SetLineWidth(1.5);
  
	//TGraphErrors *ex25 = new TGraphErrors(N_25,xbj_25, R_EX_25, Zero,R_EX_Err_25);
	TGraphErrors *ex25 = new TGraphErrors(N_25_Total,xbj_25_Total, R_EX_25_Total, Zero,R_EX_Err_25_Total);
	ex25->SetMarkerStyle(24);
	ex25->SetMarkerSize(1.5);
	ex25->SetMarkerColor(1);
	ex25->SetLineColor(1);
    ex25->SetLineWidth(1.5);
 
	TGraphErrors *ex2325 = new TGraphErrors(N_2325,xbj_2325, R_EX_2325, Zero,R_EX_Err_2325);
	ex2325->SetMarkerStyle(24);
	ex2325->SetMarkerSize(1.5);
	ex2325->SetMarkerColor(1);
	ex2325->SetLineColor(1);
    ex2325->SetLineWidth(1.5);

    TGraphErrors *ex212325 = new TGraphErrors(N_212325,xbj_212325, R_EX_212325, Zero,R_EX_Err_212325);
	ex212325->SetMarkerStyle(24);
	ex212325->SetMarkerSize(1.5);
	ex212325->SetMarkerColor(1);
	ex212325->SetLineColor(1);
    ex212325->SetLineWidth(1.5);

	TGraphErrors *ex28 = new TGraphErrors(N_28,xbj_28, R_EX_28, Zero,R_EX_Err_28);
	ex28->SetMarkerStyle(27);
	ex28->SetMarkerSize(1.9);
	ex28->SetMarkerColor(6);
	ex28->SetLineColor(6);
    ex28->SetLineWidth(1.5);
/*}}}*/

    //if(!(Target0=="C12"&&Target=="He4")){/*{{{*/
    TGraphAsymmErrors *exNF = new TGraphAsymmErrors(N_NF,xbj_NF, R_EX_NF, Zero,Zero,R_EX_Err_Down,R_EX_Err_Up);
    TGraphErrors *exNF_He4 = new TGraphErrors(N_NF,xbj_NF, R_EX_NF, Zero,R_EX_Err_NF);
    //if(Target0=="He4"&&Target=="He3"){
    if(Target=="He3"){
		//TGraphErrors *exNF = new TGraphErrors(N_NF,xbj_NF, R_EX_NF, Zero,R_EX_Err_NF);
		exNF->SetMarkerStyle(21);
		exNF->SetMarkerSize(1.3);
                exNF->SetLineWidth(1.5);
                if(Target0=="C12"&&0){
                    exNF->SetLineColor(29);
                    exNF->SetMarkerColor(29);
                    c3->cd(); exNF->Draw("P");
                }
            /*    exNF->SetMarkerColor(9);*/
                /*exNF->SetLineColor(9);*/
                c31->cd(); exNF->Draw("P");
                c32->cd(); exNF->Draw("P");
		c4->cd(); exNF->Draw("P");
		//l1->AddEntry(exNF,Form("E02019 Data (%2.0f^{#circ})",Theta_NF),"p");
		l1->AddEntry(exNF,Form("E02019 Data (18^{#circ}, Q^{2}=2.7 GeV/c^{2})"),"p");
    }
    if(Target0=="C12"&&Target=="He4" && 1){
		exNF_He4->SetMarkerStyle(21);
		exNF_He4->SetMarkerSize(1.3);
		exNF_He4->SetMarkerColor(9);
		exNF_He4->SetLineColor(9);
		exNF_He4->SetLineWidth(1.5);
		c3->cd(); exNF_He4->Draw("P");
		c31->cd(); exNF_He4->Draw("P");
		c32->cd(); exNF_He4->Draw("P");
		c4->cd(); exNF_He4->Draw("P");
		l1->AddEntry(exNF_He4,Form("E02019 Data (18^{#circ}, Q^{2}=2.7 GeV/c^{2})"),"p");
    }


	//CLAS Data
	cerr<<"---- Plotting CLAS Data"<<endl;
    TGraphErrors *exCS = new TGraphErrors(N_CS-2,xbj_CS, R_EX_CS, Zero,R_EX_Err_CS);
    if(Target0=="He4"&&Target=="He3"){
		exCS->SetMarkerStyle(29);
		exCS->SetMarkerSize(1.7);
		exCS->SetMarkerColor(2);
		exCS->SetLineColor(2);
		exCS->SetLineWidth(1.5);
		//c3->cd(); exCS->Draw("P");
		c31->cd(); exCS->Draw("P");
		c32->cd(); exCS->Draw("P");
		c4->cd(); exCS->Draw("P");
		l1->AddEntry(exCS,Form("CLAS Data"),"p");
    }

	Theta = 28.0;
	if(Target0=="C12" && Target=="He3"){
		c3->cd(); 	ex28->Draw("P");
		c4->cd(); 	ex28->Draw("P");
		//ex28->Fit("pol0","","",1.7, 2.0);
		l1->AddEntry(ex28, Form("%2.0f^{o}: %4.3f<Q^{2}<%4.3f (GeV/c^{2})",Theta,Q2_28_D,Q2_28_U),"p");
	}

	Theta = 25.0;
	c3->cd(); ex25->Draw("P");
	c4->cd(); ex25->Draw("P");
	l1->AddEntry(ex25, Form("%2.0f^{o}: %4.3f<Q^{2}<%4.3f (GeV/c^{2})",Theta,Q2_25_D,Q2_25_U),"p");
	//	ex25->Fit("pol0","","",1.5, 1.8);
   /* if(!(Target=="H2")){*/
		//c3->cd(); exQE->Draw("P");
		//c4->cd(); exQE->Draw("P");
	//}
	
	c31->cd(); ex2325->Draw("P");
	l11->AddEntry(ex2325, Form("E08014 Data (23^{#circ}, 25^{#circ}, %4.3f<Q^{2}<%4.3f GeV/c^{2})",Q2_23_D,Q2_25_U),"p");
	c32->cd(); ex212325->Draw("P");
	l12->AddEntry(ex212325, Form("E08014 Data (21^{#circ}, 23^{#circ}, 25^{#circ}, %4.3f<Q^{2}<%4.3f GeV/c^{2})",Q2_21_D,Q2_25_U),"p");
    //if(Target0=="He4"&&Target=="He3"){
    if(Target=="He3"){
        l11->AddEntry(exNF,Form("E02019 Data (18^{#circ}, Q^{2}=2.7 GeV/c^{2})"),"p");
        l12->AddEntry(exNF,Form("E02019 Data (18^{#circ}, Q^{2}=2.7 GeV/c^{2})"),"p");
    }
    if(Target0=="C12"&&Target=="He4"&&1){
	l11->AddEntry(exNF_He4,Form("E02019 Data (18^{#circ}, Q^{2}=2.7 GeV/c^{2})"),"p");
        l12->AddEntry(exNF_He4,Form("E02019 Data (18^{#circ}, Q^{2}=2.7 GeV/c^{2})"),"p");
    }
   
    if(Target0=="He4"&&Target=="He3"){
        l11->AddEntry(exCS,Form("CLAS Data"),"p");
        l12->AddEntry(exCS,Form("CLAS Data"),"p");
	}

	Theta = 23.0;
	if(!(Target=="H2")){
		c3->cd();	ex23->Draw("P");
		c4->cd();	ex23->Draw("P");
		l1->AddEntry(ex23, Form("%2.0f^{o}: %4.3f<Q^{2}<%4.3f (GeV/c^{2})",Theta,Q2_23_D,Q2_23_U),"p");
		//	ex23->Fit("pol0","","",1.7, 2.0);
	}
	Theta = 21.0;
	c3->cd();	ex21->Draw("P");
	c4->cd();	ex21->Draw("P");
	l1->AddEntry(ex21, Form("%2.0f^{o}: %4.3f<Q^{2}<%4.3f (GeV/c^{2})",Theta,Q2_21_D,Q2_21_U),"p");
	//	ex21->Fit("pol0","","",1.75, 2.0);

	if(Target=="Ca40" &&Target0=="Ca48"){
		TLine *bb = new TLine(0.7,1.0,XMax,1.0);
		bb->SetLineStyle(9);
		bb->SetLineColor(7);
		bb->SetLineWidth(2);
		TLine *b2 = new TLine(0.7,0.92,XMax,0.92);
		b2->SetLineStyle(9);
		b2->SetLineColor(8);
		b2->SetLineWidth(2);
		c3->cd(); bb->Draw();b2->Draw();
		c31->cd(); bb->Draw();b2->Draw();
		c32->cd(); bb->Draw();b2->Draw();
		c4->cd(); bb->Draw();b2->Draw();
	}/*}}}*/

	/*ALL{{{*/
	gStyle->SetOptFit(0);
	int N_ALL = N_21+N_23+N_25+N_28;
	double R_EX_ALL[N_ALL], R_EX_Err_ALL[N_ALL], xbj_ALL[N_ALL];
	int count = 0;
	for(int i=0;i<N_21;i++){
		R_EX_ALL[count] = R_EX_21[i];
		R_EX_Err_ALL[count] = R_EX_Err_21[i];
		xbj_ALL[count] = xbj_21[i];
		count++;
	}
	for(int i=0;i<N_23;i++){
		R_EX_ALL[count] = R_EX_23[i];
		R_EX_Err_ALL[count] = R_EX_Err_23[i];
		xbj_ALL[count] = xbj_23[i];
		count++;
	}
	for(int i=0;i<N_25;i++){
		R_EX_ALL[count] = R_EX_25[i];
		R_EX_Err_ALL[count] = R_EX_Err_25[i];
		xbj_ALL[count] = xbj_25[i];
		count++;
	}
	for(int i=0;i<N_28;i++){
		R_EX_ALL[count] = R_EX_28[i];
		R_EX_Err_ALL[count] = R_EX_Err_28[i];
		xbj_ALL[count] = xbj_28[i];
		count++;
	}
	TCanvas *c5 = new TCanvas("c5","c5",1200,700);
        gPad->SetGrid(1);
	c5->cd();
	TH2F *h5 = new TH2F("h5","",300,0.7,XMax,300,RMIN,RMAX);
	h5->SetStats(kFALSE);
	h5->SetXTitle("x");
	h5->GetXaxis()->CenterTitle(1);
	h5->GetXaxis()->SetTitleFont(22);
	h5->GetXaxis()->SetTitleSize(0.08);
	h5->GetXaxis()->SetTitleOffset(0.7);
	h5->GetYaxis()->SetTitle(Form("#frac{#sigma_{%s}}{#sigma_{%s}} #times #frac{%d}{%d}",lTarget0.Data(),lTarget.Data(),A2,A1));
	h5->GetYaxis()->CenterTitle(1);
	h5->GetYaxis()->SetTitleFont(22);
	h5->GetYaxis()->SetTitleSize(0.07);
	h5->GetYaxis()->SetTitleOffset(0.6);
	h5->GetYaxis()->CenterTitle();
	gPad->SetLogy(0);
	h5->Draw();

	TGraphErrors *exall = new TGraphErrors(N_ALL,xbj_ALL, R_EX_ALL, Zero,R_EX_Err_ALL);
	exall->SetMarkerStyle(24);
	exall->SetMarkerSize(1.3);
	exall->SetMarkerColor(2);
	exall->SetLineColor(2);
	c5->cd();	exall->Draw("P");
	exall->Fit("pol0","","",1.5, 1.8);
    /*}}}*/

    c3->cd(); l1->Draw();
    c31->cd(); l11->Draw();
    c32->cd(); l12->Draw();
    c4->cd(); l1->Draw();
    c3->Print(Form("./%s/%s_%s_XS_Ratio_%s_%s.png",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
    c3->Print(Form("./%s/%s_%s_XS_Ratio_%s_%s.pdf",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
    c31->Print(Form("./%s/%s_%s_XS_Ratio_%s_%s_2325.png",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
    c31->Print(Form("./%s/%s_%s_XS_Ratio_%s_%s_2325.pdf",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
    c32->Print(Form("./%s/%s_%s_XS_Ratio_%s_%s_212325.png",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
    c32->Print(Form("./%s/%s_%s_XS_Ratio_%s_%s_212325.pdf",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
    //c4->Print(Form("./%s/%s_%s_XS_Ratio_%s_%s_Zoom.png",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
    //c4->Print(Form("./%s/%s_%s_XS_Ratio_%s_%s_Zoom.pdf",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));

    /*MC{{{*/
    if(bMC){	
        TGraphErrors *mc21 = new TGraphErrors(N_21,xbj_21, R_MC_21, Zero, Zero);
        mc21->SetLineWidth(2);
        mc21->SetLineColor(2);
        //mc21->SetLineColor(46);
        mc21->SetLineStyle(8);
        c3->cd(); mc21->Draw("l");
        c4->cd(); mc21->Draw("l");

        TGraphErrors *mc23 = new TGraphErrors(N_23,xbj_23, R_MC_23, Zero, Zero);
        mc23->SetLineWidth(2);
        mc23->SetLineStyle(3);
        //mc23->SetLineColor(9);
        mc23->SetLineColor(4);
        c3->cd();	mc23->Draw("l");
        c4->cd();	mc23->Draw("l");

        TGraphErrors *mcQE = new TGraphErrors(N_QE,xbj_QE, R_MC_QE, Zero, Zero);
        mcQE->SetLineWidth(2);
        mcQE->SetLineStyle(5);
        mcQE->SetLineColor(1);
        //mcQE->SetLineColor(12);
        c3->cd();	mcQE->Draw("l");
        c4->cd();	mcQE->Draw("l");

        //TGraphErrors *mc25 = new TGraphErrors(N_25,xbj_25, R_MC_25, Zero, Zero);
        TGraphErrors *mc25 = new TGraphErrors(N_25_Total,xbj_25_Total, R_MC_25_Total, Zero, Zero);
        mc25->SetLineWidth(2);
        mc25->SetLineStyle(5);
        mc25->SetLineColor(1);
        //mc25->SetLineColor(12);
        c3->cd();	mcQE->Draw("l");
        c3->cd();	mc25->Draw("l");
        c4->cd();	mc25->Draw("l");

        
        TGraphErrors *mc2325 = new TGraphErrors(N_2325,xbj_2325, R_MC_2325, Zero, Zero);
        mc2325->SetLineWidth(2);
        mc2325->SetLineStyle(1);
        mc2325->SetLineColor(1);
        c31->cd();	mc2325->Draw("l");
        l11->AddEntry(mc2325, Form("R_{MC} at %d^{#circ} and %d^{#circ}",23,25),"l");

        TGraphErrors *mc212325 = new TGraphErrors(N_212325,xbj_212325, R_MC_212325, Zero, Zero);
        mc212325->SetLineWidth(2);
        mc212325->SetLineColor(1);
        mc212325->SetLineStyle(1);
        c32->cd();	mc212325->Draw("l");
        l12->AddEntry(mc212325, Form("R_{MC} at %d^{#circ}, %d^{#circ} and %d^{#circ}",21,23,25),"l");

        TGraphErrors *mc28 = new TGraphErrors(N_28,xbj_28, R_MC_28, Zero, Zero);
        mc28->SetLineWidth(2);
        mc28->SetLineColor(6);
        //mc28->SetLineColor(40);
        mc28->SetLineStyle(6);
        if(Target0=="C12"&&Target=="He3"){
            c3->cd();	mc28->Draw("l");
            c4->cd();	mc28->Draw("l");
            l1->AddEntry(mc28, Form("R_{MC} at %d^{#circ}",28),"l");
        }

        l1->AddEntry(mc25, Form("R_{MC} at %d^{#circ}",25),"l");
        l1->AddEntry(mc23, Form("R_{MC} at %d^{#circ}",23),"l");
        l1->AddEntry(mc21, Form("R_{MC} at %d^{#circ}",21),"l");


        //c3->cd(); l1->Draw();
        //c31->cd(); l11->Draw();
        //c32->cd(); l12->Draw();
        //c4->cd(); l1->Draw();
        c3->Print(Form("./%s/%s_%s_XS_Ratio_MC_%s_%s.png",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
        c3->Print(Form("./%s/%s_%s_XS_Ratio_MC_%s_%s.pdf",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
        c31->Print(Form("./%s/%s_%s_XS_Ratio_MC_%s_%s_2325.png",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
        c31->Print(Form("./%s/%s_%s_XS_Ratio_MC_%s_%s_2325.pdf",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
        c32->Print(Form("./%s/%s_%s_XS_Ratio_MC_%s_%s_212325.png",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
        c32->Print(Form("./%s/%s_%s_XS_Ratio_MC_%s_%s_212325.pdf",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
        //c4->Print(Form("./%s/%s_%s_XS_Ratio_MC_%s_%s_Zoom.png",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
        //c4->Print(Form("./%s/%s_%s_XS_Ratio_MC_%s_%s_Zoom.pdf",OutFile_Dir.Data(), Target0.Data(),Target.Data(),Com0.Data(),Com.Data()));
    }
    /*}}}*/

	/*}}}*/
	return 0;
}
/*}}}*/

