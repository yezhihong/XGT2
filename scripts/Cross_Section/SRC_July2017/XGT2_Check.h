  //////////////////////////
  // Check Data and Cuts
  //////////////////////////
/*Make Plots{{{*/
inline void gMake_Plot(TChain *aT_EX,const TString& aEX_Cut,TChain *aT_MC,const Double_t aAccCut[9],
        const TString& aTarget,const Bool_t aIsExtTgt, const TString& aArm,const TString& aKin,const TString& aPath, 
        const Double_t aP0,const Double_t aAngle, const Double_t aNe, const Double_t aLiveTime, const Double_t aNtg,
        const Double_t aI_avg, const Double_t aMC_PhaseSpace, const TString& aCom, Get_XS* aXS)
{

    const double aEX_NORM = CM2ToNB/(aNe * aLiveTime );
    const double aMC_NORM = aNtg * aMC_PhaseSpace *10.; // 10 means I only read in 10% of the MC data for plotting

    gStyle->SetOptStat(0);

    const double aE0 = 3.356;
    double norm = 1.0;
    double scale = 1.0;
    const double aL_Ph_Offset= 0.002;
    const double aR_Ph_Offset=-0.002;
    double aPhi_Offset= 0.0;

    if(aArm=="L") aPhi_Offset = Phi_Offset_L;
    if(aArm=="R") aPhi_Offset = Phi_Offset_R;

    /*Making Histograms from Experimental Data{{{*/
    cout<<"      ### Making Histograms for the Experimental Data"<<endl;
    cout<<"      ###        Using the cuts: "<<aEX_Cut.Data()<<endl;
    outlog<<"      ### Making Histograms for the Experimental Data"<<endl;
    outlog<<"      ###        Using the cuts: "<<aEX_Cut.Data()<<endl;
    /*Focal Plane{{{*/
    //X_fp
    TH1F *h_xfp = new TH1F("h_xfp","", 100, -1.15,1.15);
    h_xfp->SetXTitle("x_{fp}");
    h_xfp->SetLineColor(2); 
    h_xfp->SetLineWidth(1.1);
    h_xfp->GetXaxis()->SetTitleSize(0.08);
    h_xfp->GetXaxis()->SetTitleOffset(0.7);
    h_xfp->GetXaxis()->CenterTitle(1);

    //Y_fp
    TH1F *h_yfp = new TH1F("h_yfp","", 100, -0.05,0.05);
    h_yfp->SetXTitle("y_{fp}");
    h_yfp->SetLineColor(2); 
    h_yfp->SetLineWidth(1.1);
    h_yfp->GetXaxis()->SetTitleSize(0.08);
    h_yfp->GetXaxis()->SetTitleOffset(0.7);
    h_yfp->GetXaxis()->CenterTitle(1);

    //Th_fp
    TH1F *h_tfp = new TH1F("h_tfp","", 100, -0.04,0.04);
    h_tfp->SetXTitle("#theta_{fp}");
    h_tfp->SetLineColor(2); 
    h_tfp->SetLineWidth(1.1);
    h_tfp->GetXaxis()->SetTitleSize(0.08);
    h_tfp->GetXaxis()->SetTitleOffset(0.7);
    h_tfp->GetXaxis()->CenterTitle(1);

    //Ph_fp
    TH1F *h_pfp = new TH1F("h_pfp","", 100, -0.06,0.06);
    h_pfp->SetXTitle("#phi_{fp}");
    h_pfp->SetLineColor(2); 
    h_pfp->SetLineWidth(1.1);
    h_pfp->GetXaxis()->SetTitleSize(0.08);
    h_pfp->GetXaxis()->SetTitleOffset(0.7);
    h_pfp->GetXaxis()->CenterTitle(1);
    /*}}}*/

    /*Target Plane{{{*/
    //DeltaP
    TH1F *h_dtg = new TH1F("h_dtg","", 100, -0.07,0.07);
    h_dtg->SetXTitle("#delta P");
    h_dtg->SetLineColor(2); 
    h_dtg->SetLineWidth(1.1);
    h_dtg->GetXaxis()->SetTitleSize(0.08);
    h_dtg->GetXaxis()->SetTitleOffset(0.7);
    h_dtg->GetXaxis()->CenterTitle(1);

    //Y_tg  
    TH1F *h_ytg = new TH1F("h_ytg","", 100, -0.04,0.04);
    h_ytg->SetXTitle("y_{tg}");
    h_ytg->SetLineColor(2); 
    h_ytg->SetLineWidth(1.1);
    h_ytg->GetXaxis()->SetTitleSize(0.08);
    h_ytg->GetXaxis()->SetTitleOffset(0.7);
    h_ytg->GetXaxis()->CenterTitle(1);

    //Z_react
    TH1F *h_ztg = new TH1F("h_ztg","", 100, -0.12,0.12);
    h_ztg->SetXTitle("z_{react}");
    h_ztg->SetLineColor(2); 
    h_ztg->SetLineWidth(1.1);
    h_ztg->GetXaxis()->SetTitleSize(0.08);
    h_ztg->GetXaxis()->SetTitleOffset(0.7);
    h_ztg->GetXaxis()->CenterTitle(1);

    //Th_tg  
    TH1F *h_ttg = new TH1F("h_ttg","", 100, -0.07,0.07);
    h_ttg->SetXTitle("#theta_{tg}");
    h_ttg->SetLineColor(2); 
    h_ttg->SetLineWidth(1.1);
    h_ttg->GetXaxis()->SetTitleSize(0.08);
    h_ttg->GetXaxis()->SetTitleOffset(0.7);
    h_ttg->GetXaxis()->CenterTitle(1);

    //Ph_tg  
    TH1F *h_ptg = new TH1F("h_ptg","", 100, -0.05,0.05);
    h_ptg->SetXTitle("#phi_{tg}");
    h_ptg->SetLineColor(2); 
    h_ptg->SetLineWidth(1.1);
    h_ptg->GetXaxis()->SetTitleSize(0.08);
    h_ptg->GetXaxis()->SetTitleOffset(0.7);
    h_ptg->GetXaxis()->CenterTitle(1);


    //xbj   
    double Xbj_Max = 4.0;
    double Xbj_Min = 0.8;
    if(aKin.Contains("5.0")&&!(aKin.Contains("5.05"))){
        Xbj_Min = 0.65;
        Xbj_Max = 1.4;
    }
    if(aKin.Contains("5.05")){
        Xbj_Min = 0.8;
        Xbj_Max = 1.8;
    }
    if(aKin.Contains("3.1")||aKin.Contains("4.1")||aKin.Contains("5.1")){
        Xbj_Min = 1.0;
        Xbj_Max = 2.5;
    }
    if(aKin.Contains("3.2")||aKin.Contains("4.2")||aKin.Contains("5.2")||aKin.Contains("6.5")){
        Xbj_Min = 1.5;
        Xbj_Max = 4.0;
        if(aTarget=="He3")
            Xbj_Max = 3.2;
    }

    TH1F *h_xbj = new TH1F("h_xbj","", 400, Xbj_Min,Xbj_Max);
    h_xbj->SetXTitle("x_{bj}");
    h_xbj->SetLineColor(2); 
    h_xbj->SetLineWidth(1.1);
    h_xbj->GetXaxis()->SetTitleSize(0.08);
    h_xbj->GetXaxis()->SetTitleOffset(0.7);
    h_xbj->GetXaxis()->CenterTitle(1);
    /*}}}*/

    /*Define Acceptance Variables{{{*/
    double aSinA = sin(aAngle*TMath::DegToRad());
    double aCosA = cos(aAngle*TMath::DegToRad());
    double aSinSQ = pow(sin(aAngle*TMath::DegToRad()/2.0),2); //Define Sin(Theta/2.)^2

    TString aEX_Dp, aEX_Th, aEX_Ph;

    aEX_Dp= Form("ExTgt%s.dp",aArm.Data());
    if(aArm=="R")
        aEX_Dp = gGet_Delta_Correct(aArm,  aIsExtTgt);

    if(aIsExtTgt){
        aEX_Th = Form("ExTgt%s.th",aArm.Data());
        aEX_Ph = Form("(ExTgt%s.ph-%f)",aArm.Data(),aPhi_Offset);
    }else{
        aEX_Th = Form("%s.gold.th",aArm.Data());
        aEX_Ph = Form("(%s.gold.ph-%f)",aArm.Data(),aPhi_Offset);
    }

    TString aEX_SA = Form("acos((%f-%s*%f)/sqrt(1.0+pow(%s,2)+pow(%s,2)))",aCosA,aEX_Ph.Data(),aSinA,aEX_Th.Data(),aEX_Ph.Data());
    TString aEX_SinSQ = Form("pow(sin(%s/2.0),2)",aEX_SA.Data()); //Define Sin(Theta/2.)^2

    TString aEX_Ep =Form("(%7.5f*(1.0+%s))",aP0,aEX_Dp.Data());
    TString aEX_Nu= Form("(%7.5f-%7.5f*(1.0+%s))",aE0,aP0,aEX_Dp.Data());
    TString aEX_Q2 = Form("4.0*%7.5f*(%7.5f*(1.0+%s))*%s",aE0,aP0,aEX_Dp.Data(),aEX_SinSQ.Data());
    TString aEX_Xbj=Form("%s/(2.0*%8.6f*%s)",aEX_Q2.Data(),PROTON_MASS,aEX_Nu.Data());
    cerr<<"---Xbj = "<<aEX_Xbj.Data()<<endl;
    /*}}}*/

    /*Ploting EX Data{{{*/
    aT_EX->Project("h_xfp",Form("%s.tr.r_x", aArm.Data()),aEX_Cut);
    aT_EX->Project("h_yfp",Form("%s.tr.r_y", aArm.Data()),aEX_Cut);
    aT_EX->Project("h_tfp",Form("%s.tr.r_th",aArm.Data()),aEX_Cut);
    aT_EX->Project("h_pfp",Form("%s.tr.r_ph",aArm.Data()),aEX_Cut);

    aT_EX->Project("h_ytg",Form("ExTgt%s.y",aArm.Data()),aEX_Cut);
    aT_EX->Project("h_ztg",Form("RctPt%s.z",aArm.Data()),aEX_Cut);
    aT_EX->Project("h_dtg",aEX_Dp.Data(),aEX_Cut);
    aT_EX->Project("h_ttg",aEX_Th.Data(),aEX_Cut);
    aT_EX->Project("h_ptg",aEX_Ph.Data(),aEX_Cut);
    //aEX_Xbj=Form("ExtEK%s.x_bj",aArm.Data());
    aT_EX->Project("h_xbj",aEX_Xbj.Data(),aEX_Cut);

    //scale = norm/h_xfp->Integral(); h_xfp->Scale(scale);
    //scale = norm/h_yfp->Integral(); h_yfp->Scale(scale);
    //scale = norm/h_tfp->Integral(); h_tfp->Scale(scale);
    //scale = norm/h_pfp->Integral(); h_pfp->Scale(scale);
    //scale = norm/h_dtg->Integral(); h_dtg->Scale(scale);
    //scale = norm/h_ytg->Integral(); h_ytg->Scale(scale);
    //scale = norm/h_ztg->Integral(); h_ztg->Scale(scale);
    //scale = norm/h_ttg->Integral(); h_ttg->Scale(scale);
    //scale = norm/h_ptg->Integral(); h_ptg->Scale(scale);
    //scale = norm/h_xbj->Integral(); h_xbj->Scale(scale);

    h_xfp->Scale(aEX_NORM);
    h_yfp->Scale(aEX_NORM);
    h_tfp->Scale(aEX_NORM);
    h_pfp->Scale(aEX_NORM);
    h_dtg->Scale(aEX_NORM);
    h_ytg->Scale(aEX_NORM);
    h_ztg->Scale(aEX_NORM);
    h_ttg->Scale(aEX_NORM);
    h_ptg->Scale(aEX_NORM);
    h_xbj->Scale(aEX_NORM);

    /*}}}*/
    /*}}}*/

    /*Making Histograms from MC Data{{{*/
    cout<<"      ### Making Histograms for the MC Data"<<endl;
    outlog<<"      ### Making Histograms for the MC Data"<<endl;
    cout<<Form("    ### MC Cuts are: f(fabs(x_fp)<%5.3f && fabs(y_fp)<%5.3f&&fabs(th_fp)<%5.3f&&fabs(ph_fp)<%5.3f&&fabs(dp_rec)<%5.3f&&fabs(y_tg_rec)<%5.3f&&fabs(th_tg_rec)<%5.3f&&fabs(ph_tg_rec)<%5.3f&&fabs(reactz_rec)<%5.3f.",
            aAccCut[0], aAccCut[1], aAccCut[2], aAccCut[3], aAccCut[4], aAccCut[5], aAccCut[6], aAccCut[7], aAccCut[8])<<endl;
    outlog<<Form("    ### MC Cuts are: f(fabs(x_fp)<%5.3f && fabs(y_fp)<%5.3f&&fabs(th_fp)<%5.3f&&fabs(ph_fp)<%5.3f&&fabs(dp_rec)<%5.3f&&fabs(y_tg_rec)<%5.3f&&fabs(th_tg_rec)<%5.3f&&fabs(ph_tg_rec)<%5.3f&&fabs(reactz_rec)<%5.3f.",
            aAccCut[0], aAccCut[1], aAccCut[2], aAccCut[3], aAccCut[4], aAccCut[5], aAccCut[6], aAccCut[7], aAccCut[8])<<endl;

    /*Focal Plane{{{*/
    //X_fp
    TH1F *m_xfp = new TH1F("m_xfp","", 100,-1.15,1.15);
    m_xfp->SetXTitle("x_{fp}");
    m_xfp->SetLineColor(4); 
    m_xfp->SetLineWidth(1.1);
    m_xfp->GetXaxis()->SetTitleSize(0.08);
    m_xfp->GetXaxis()->SetTitleOffset(0.7);
    m_xfp->GetXaxis()->CenterTitle(1);
    //Y_fp
    TH1F *m_yfp = new TH1F("m_yfp","", 100, -0.05,0.05);
    m_yfp->SetXTitle("y_{fp}");
    m_yfp->SetLineColor(4); 
    m_yfp->SetLineWidth(1.1);
    m_yfp->GetXaxis()->SetTitleSize(0.08);
    m_yfp->GetXaxis()->SetTitleOffset(0.7);
    m_yfp->GetXaxis()->CenterTitle(1);
    //Th_fp
    TH1F *m_tfp = new TH1F("m_tfp","", 100, -0.04,0.04);
    m_tfp->SetXTitle("#theta_{fp}");
    m_tfp->SetLineColor(4); 
    m_tfp->SetLineWidth(1.1);
    m_tfp->GetXaxis()->SetTitleSize(0.08);
    m_tfp->GetXaxis()->SetTitleOffset(0.7);
    m_tfp->GetXaxis()->CenterTitle(1);
    //Ph_fp
    TH1F *m_pfp = new TH1F("m_pfp","", 100, -0.06,0.06);
    m_pfp->SetXTitle("#phi_{fp}");
    m_pfp->SetLineColor(4); 
    m_pfp->SetLineWidth(1.1);
    m_pfp->GetXaxis()->SetTitleSize(0.08);
    m_pfp->GetXaxis()->SetTitleOffset(0.7);
    m_pfp->GetXaxis()->CenterTitle(1);
    /*}}}*/

    /*Target Plane{{{*/
    //DeltaP
    TH1F *m_dtg = new TH1F("m_dtg","", 100, -0.07,0.07);
    m_dtg->SetXTitle("#delta P");
    m_dtg->SetLineColor(4); 
    m_dtg->SetLineWidth(1.1);
    m_dtg->GetXaxis()->SetTitleSize(0.08);
    m_dtg->GetXaxis()->SetTitleOffset(0.7);
    m_dtg->GetXaxis()->CenterTitle(1);
    //Y_tg  
    TH1F *m_ytg = new TH1F("m_ytg","", 100, -0.04,0.04);
    m_ytg->SetXTitle("y_{tg}");
    m_ytg->SetLineColor(4); 
    m_ytg->SetLineWidth(1.1);
    m_ytg->GetXaxis()->SetTitleSize(0.08);
    m_ytg->GetXaxis()->SetTitleOffset(0.7);
    m_ytg->GetXaxis()->CenterTitle(1);
    //Z_react
    TH1F *m_ztg = new TH1F("m_ztg","", 100, -0.12,0.12);
    m_ztg->SetXTitle("z_{react}");
    m_ztg->SetLineColor(4); 
    m_ztg->SetLineWidth(1.1);
    m_ztg->GetXaxis()->SetTitleSize(0.08);
    m_ztg->GetXaxis()->SetTitleOffset(0.7);
    m_ztg->GetXaxis()->CenterTitle(1);
    //Th_tg  
    TH1F *m_ttg = new TH1F("m_ttg","", 100, -0.07,0.07);
    m_ttg->SetXTitle("#theta_{tg}");
    m_ttg->SetLineColor(4); 
    m_ttg->SetLineWidth(1.1);
    m_ttg->GetXaxis()->SetTitleSize(0.08);
    m_ttg->GetXaxis()->SetTitleOffset(0.7);
    m_ttg->GetXaxis()->CenterTitle(1);
    //Ph_tg  
    TH1F *m_ptg = new TH1F("m_ptg","", 100, -0.05,0.05);
    m_ptg->SetXTitle("#phi_{tg}");
    m_ptg->SetLineColor(4); 
    m_ptg->SetLineWidth(1.1);
    m_ptg->GetXaxis()->SetTitleSize(0.08);
    m_ptg->GetXaxis()->SetTitleOffset(0.7);
    m_ptg->GetXaxis()->CenterTitle(1);
    //xbj
    TH1F *m_xbj = new TH1F("m_xbj","", 400, Xbj_Min,Xbj_Max);
    m_xbj->SetXTitle("x_{bj}");
    m_xbj->SetLineColor(4); 
    m_xbj->SetLineWidth(1.1);
    m_xbj->GetXaxis()->SetTitleSize(0.08);
    m_xbj->GetXaxis()->SetTitleOffset(0.7);
    m_xbj->GetXaxis()->CenterTitle(1);
    /*}}}*/

    /*Fill Histograms{{{*/
    /*Set BranchAddress{{{*/
    int IsPassed,IsQualified;
    double x_fp,y_fp,th_fp,ph_fp,x_tg_rec, y_tg_rec,th_tg_rec,ph_tg_rec,dp_rec,reactz_rec,Angle_rec;
    aT_MC->SetBranchAddress("IsPassed",&IsPassed); //if pass through the magnet, 1=true, 0=false(not pass)
    aT_MC->SetBranchAddress("IsQualified",&IsQualified); //if rec var is in the range of gen, 1=true, 0=false(not
    aT_MC->SetBranchAddress("x_fp",&x_fp    ); //
    aT_MC->SetBranchAddress("y_fp",&y_fp    ); //
    aT_MC->SetBranchAddress("th_fp",&th_fp    ); //
    aT_MC->SetBranchAddress("ph_fp",&ph_fp    ); //
    aT_MC->SetBranchAddress("x_tg_rec",&x_tg_rec    ); //cm
    aT_MC->SetBranchAddress("y_tg_rec",&y_tg_rec    ); //cm
    aT_MC->SetBranchAddress("th_tg_rec",&th_tg_rec    ); //
    aT_MC->SetBranchAddress("ph_tg_rec",&ph_tg_rec    ); //
    aT_MC->SetBranchAddress("dp_rec",&dp_rec    );
    aT_MC->SetBranchAddress("Angle_rec",&Angle_rec    );
    aT_MC->SetBranchAddress("reactz_rec",&reactz_rec    );

    double E_s, E_p, Theta,Xbj;
    aT_MC->SetBranchAddress("E_s",&E_s);
    aT_MC->SetBranchAddress("E_p",&E_p);
    aT_MC->SetBranchAddress("Theta",&Theta);
    aT_MC->SetBranchAddress("Xbj",&Xbj);
    /*}}}*/
    Int_t Evt = aT_MC->GetEntries();
    
    /*Target Density{{{*/
    //const Int_t aBin_Rho = 52;
    //const double aVZ_Max = 0.1020, aVZ_Min = -0.1020;
    //const double aStep = (aVZ_Max-aVZ_Min)/51.;//0.004

    const Int_t aBin_Rho = 200;
    const double aVZ_Max = 0.095, aVZ_Min = -0.095;
    const double aStep = (aVZ_Max-aVZ_Min)/(aBin_Rho-1);//0.001

    double aVZ[aBin_Rho], aRho[aBin_Rho], aRho1[aBin_Rho],aRho2[aBin_Rho],aRho3[aBin_Rho];
    for(int i=0;i<aBin_Rho;i++){
        aVZ[i] = 0.0; aRho[i] = 1.0; aRho2[i] = 1.0; aRho3[i] = 1.0;
    }
    double aRho_Sum = 0;
    TString aDummy="X";

    if(aTarget=="H2"||aTarget=="He3"||aTarget=="He4"){
        TString aDensity_Profile = Form("/work/halla/e08014/disk1/yez/Xbj_Cross_Section/Target/%s_new.rho",aTarget.Data());
        cerr<<Form("\t Reading Density Profile for %s from %s",aTarget.Data(), aDensity_Profile.Data())<<endl;
        ifstream density(aDensity_Profile.Data()); 
        density >> aDummy >> aDummy >> aDummy >> aDummy >> aDummy;
        Double_t aY0, aY0_Err, aBF, aBF_Err;
        for(int i=0;i<aBin_Rho;i++){
            density >> aVZ[i] >> aY0 >> aY0_Err >> aBF >> aBF_Err;
            aVZ[i] /= 100.; //cm to m
            aRho3[i] = aY0 * (1+aBF * aI_avg);
            aRho_Sum += aRho3[i];
            cout<<Form("    &&& VZ = %f,  Rho = %f", aVZ[i], aRho3[i])<<endl;
        }
        density.close();
        aRho_Sum /=aBin_Rho;
    }
    /*}}}*/

    /*Loop and Fill{{{*/
    Double_t kTheta = 0.0, aCS = 0.0, aCS_Center = 0.0, aSum = 0.0, aSum_Center=0.0;
    Int_t aCount = 0;

    int aVZ_Bin = 0;  double aWeight=1.0;
    for(int j=0;j<Evt/10;j++){
        aT_MC->GetEntry(j);

        double E_p_new = aP0 * (1+dp_rec);
        double aSinA = sin(aAngle*TMath::DegToRad());
        double aCosA = cos(aAngle*TMath::DegToRad());
        double Angle_new = acos( (aCosA-ph_tg_rec*aSinA)/sqrt(1.+pow(th_tg_rec,2)+pow(ph_tg_rec,2))); 
        double Q2_new = 4.0*E_s*E_p_new*pow( sin(Angle_new/2.), 2);
        double xbj_new = Q2_new/2./TARGET_MASS_A/(E_s-E_p_new);

        if(fabs(x_fp)       < aAccCut[0] &&
                fabs(y_fp)       < aAccCut[1] &&
                fabs(th_fp)      < aAccCut[2] &&
                fabs(ph_fp)      < aAccCut[3] &&
                fabs(dp_rec)     < aAccCut[4] &&
                fabs(y_tg_rec)   < aAccCut[5] &&
                fabs(th_tg_rec)  < aAccCut[6] &&
                fabs(ph_tg_rec)  < aAccCut[7] &&
                fabs(reactz_rec) < aAccCut[8] &&
                IsPassed==1 ){

            double E_p_new = aP0 * (1+dp_rec);
            double Angle_new = acos( (aCosA-ph_tg_rec*aSinA)/sqrt(1.+pow(th_tg_rec,2)+pow(ph_tg_rec,2))); 
            double Q2_new = 4.0*E_s*E_p_new*pow( sin(Angle_new/2.), 2);
            double xbj_new = Q2_new/2./PROTON_MASS/(E_s-E_p_new);

            if(aTarget=="H2"||aTarget=="He3"||aTarget=="He4"){
                aVZ_Bin = (reactz_rec-aVZ_Min)/aStep;
                aWeight = aRho3[aVZ_Bin]/aRho_Sum; 
            }else
                aWeight = 1.0;

            aCS = aXS->gGet_XS(E_s,E_p_new,abs(Angle_new*180./3.1415926));
            double weight = aWeight * aCS;

            m_xfp->Fill(x_fp,weight);
            m_yfp->Fill(y_fp,weight);
            m_tfp->Fill(th_fp,weight);
            m_pfp->Fill(ph_fp,weight);

            m_dtg->Fill(dp_rec,weight);
            m_ytg->Fill(y_tg_rec,weight);
            m_ztg->Fill(reactz_rec,weight);
            m_ttg->Fill(th_tg_rec,weight);
            m_ptg->Fill(ph_tg_rec,weight);
            m_xbj->Fill(xbj_new,weight);
        }

    }
    /*}}}*/

    //scale = norm/m_xfp->Integral(); m_xfp->Scale(scale);
    //scale = norm/m_yfp->Integral(); m_yfp->Scale(scale);
    //scale = norm/m_tfp->Integral(); m_tfp->Scale(scale);
    //scale = norm/m_pfp->Integral(); m_pfp->Scale(scale);
    //scale = norm/m_dtg->Integral(); m_dtg->Scale(scale);
    //scale = norm/m_ytg->Integral(); m_ytg->Scale(scale);
    //scale = norm/m_ztg->Integral(); m_ztg->Scale(scale);
    //scale = norm/m_ttg->Integral(); m_ttg->Scale(scale);
    //scale = norm/m_ptg->Integral(); m_ptg->Scale(scale);
    //scale = norm/m_xbj->Integral(); m_xbj->Scale(scale);

    m_xfp->Scale(aMC_NORM);
    m_yfp->Scale(aMC_NORM);
    m_tfp->Scale(aMC_NORM);
    m_pfp->Scale(aMC_NORM);
    m_dtg->Scale(aMC_NORM);
    m_ytg->Scale(aMC_NORM);
    m_ztg->Scale(aMC_NORM);
    m_ttg->Scale(aMC_NORM);
    m_ptg->Scale(aMC_NORM);
    m_xbj->Scale(aMC_NORM);

    /*}}}*/

    /*}}}*/

    /*Plot{{{*/
    TH1F *r_xfp = (TH1F*) h_xfp->Clone("r_xfp"); r_xfp->Divide(m_xfp); r_xfp->GetXaxis()->SetTitleSize(0.08);
    TH1F *r_yfp = (TH1F*) h_yfp->Clone("r_yfp"); r_yfp->Divide(m_yfp); r_yfp->GetXaxis()->SetTitleSize(0.08);
    TH1F *r_tfp = (TH1F*) h_tfp->Clone("r_tfp"); r_tfp->Divide(m_tfp); r_tfp->GetXaxis()->SetTitleSize(0.08);
    TH1F *r_pfp = (TH1F*) h_pfp->Clone("r_pfp"); r_pfp->Divide(m_pfp); r_pfp->GetXaxis()->SetTitleSize(0.08);


    r_xfp->SetTitle(Form("x_{fp} Ratio (EX/MC) %s@%s (#%s)",     aTarget.Data(),aKin.Data(),aArm.Data())); 
    r_xfp->SetLineColor(1);//r_xfp->SetTitleSize(2.3); 
    r_yfp->SetTitle(Form("y_{fp} Ratio (EX/MC) %s@%s (#%s)",     aTarget.Data(),aKin.Data(),aArm.Data())); 
    r_yfp->SetLineColor(1);    //r_yfp->SetTitleSize(2.3);
    r_tfp->SetTitle(Form("#theta_{fp} Ratio (EX/MC) %s@%s (#%s)",aTarget.Data(),aKin.Data(),aArm.Data())); 
    r_tfp->SetLineColor(1);//r_tfp->SetTitleSize(2.3); 
    r_pfp->SetTitle(Form("#phi_{fp} Ratio (EX/MC) %s@%s (#%s)",  aTarget.Data(),aKin.Data(),aArm.Data())); 
    r_pfp->SetLineColor(1);       //r_pfp->SetTitleSize(2.3); 

    TH1F *r_dtg = (TH1F*) h_dtg->Clone("r_dtg"); r_dtg->Divide(m_dtg);r_dtg->GetXaxis()->SetTitleSize(0.08);
    TH1F *r_ytg = (TH1F*) h_ytg->Clone("r_ytg"); r_ytg->Divide(m_ytg);r_ytg->GetXaxis()->SetTitleSize(0.08);
    TH1F *r_ztg = (TH1F*) h_ztg->Clone("r_ztg"); r_ztg->Divide(m_ztg);r_ztg->GetXaxis()->SetTitleSize(0.08);
    TH1F *r_ttg = (TH1F*) h_ttg->Clone("r_ttg"); r_ttg->Divide(m_ttg);r_ttg->GetXaxis()->SetTitleSize(0.08);
    TH1F *r_ptg = (TH1F*) h_ptg->Clone("r_ptg"); r_ptg->Divide(m_ptg);r_ptg->GetXaxis()->SetTitleSize(0.08);

    r_dtg->SetTitle(Form("#deltaP Ratio (EX/MC) %s@%s (#%s)",    aTarget.Data(),aKin.Data(),aArm.Data())); 
    r_dtg->SetLineColor(1);    //r_dtg->SetTitleSize(2.3); 
    r_ztg->SetTitle(Form("ReactZ Ratio (EX/MC) %s@%s (#%s)",     aTarget.Data(),aKin.Data(),aArm.Data()));
    r_ztg->SetLineColor(1);    //r_ztg->SetTitleSize(2.3); 
    r_ytg->SetTitle(Form("y_{tg} Ratio (EX/MC) %s@%s (#%s)",     aTarget.Data(),aKin.Data(),aArm.Data()));
    r_ytg->SetLineColor(1);    //r_ytg->SetTitleSize(2.3);
    r_ttg->SetTitle(Form("#theta_{tg} Ratio (EX/MC) %s@%s (#%s)",aTarget.Data(),aKin.Data(),aArm.Data()));
    r_ttg->SetLineColor(1);   //r_ttg->SetTitleSize(2.3); 
    r_ptg->SetTitle(Form("#phi_{tg} Ratio (EX/MC) %s@%s (#%s)",  aTarget.Data(),aKin.Data(),aArm.Data())); 
    r_ptg->SetLineColor(1);        //r_ptg->SetTitleSize(2.3);

    TCanvas *c0 = new TCanvas("c0","c0 Focal Plane",800,1000);
    c0->Clear();
    c0->Divide(2,4);
    gPad->SetLogy(0);
    c0->cd(1); r_xfp->Draw();
    c0->cd(3); r_yfp->Draw();
    c0->cd(5); r_tfp->Draw();
    c0->cd(7); r_pfp->Draw();

    c0->cd(2); r_dtg->Draw();
    c0->cd(4); r_ztg->Draw();
    //c0->cd(4); r_ytg->Draw();
    c0->cd(6); r_ttg->Draw();
    c0->cd(8); r_ptg->Draw();

    TString pic=aPath+"/" + aTarget+"_"+aKin+"_"+Form("%s_3_ratio_%s.png",aArm.Data(), aCom.Data());
    cout<<"      ### Saving plot: "<< pic.Data()<<endl;
    outlog<<"      ### Saving plot: "<< pic.Data()<<endl;
    c0->Print(pic);


    TCanvas *c1 = new TCanvas("c1","c1 Focal Plane",800,1000);
    c1->Clear();
    c1->Divide(2,4);
    gPad->SetLogy(0);
    c1->cd(1); m_xfp->Draw();
    c1->cd(3); m_yfp->Draw();
    c1->cd(5); m_tfp->Draw();
    c1->cd(7); m_pfp->Draw();
    c1->cd(1); h_xfp->Draw("same");  
    c1->cd(3); h_yfp->Draw("same"); 
    c1->cd(5); h_tfp->Draw("same"); 
    c1->cd(7); h_pfp->Draw("same"); 

    c1->cd(2);gPad->SetLogy(1);gPad->SetGridy(1);r_xfp->GetYaxis()->SetRangeUser(0.1,10.);r_xfp->Draw("");  
    c1->cd(4);gPad->SetLogy(1);gPad->SetGridy(1);r_yfp->GetYaxis()->SetRangeUser(0.1,10.);r_yfp->Draw(""); 
    c1->cd(6);gPad->SetLogy(1);gPad->SetGridy(1);r_tfp->GetYaxis()->SetRangeUser(0.1,10.);r_tfp->Draw(""); 
    c1->cd(8);gPad->SetLogy(1);gPad->SetGridy(1);r_pfp->GetYaxis()->SetRangeUser(0.1,10.);r_pfp->Draw(""); 

    pic=aPath+"/"  + aTarget+"_"+aKin+"_"+Form("%s_1_fp_%s.png",aArm.Data(), aCom.Data());
    cout<<"      ### Saving plot: "<< pic.Data()<<endl;
    outlog<<"      ### Saving plot: "<< pic.Data()<<endl;
    c1->Print(pic);

    TCanvas *c2 = new TCanvas("c2","c2 Target Plane",800,1000);
    c2->Clear();
    c2->Divide(2,4);

    gPad->SetLogy(0);
    c2->cd(1); m_dtg->Draw();
    c2->cd(3); m_ztg->Draw();
    //c2->cd(3); m_ytg->Draw();
    c2->cd(5); m_ttg->Draw();
    c2->cd(7); m_ptg->Draw();

    c2->cd(1); h_dtg->Draw("same");  
    c2->cd(3); h_ztg->Draw("same"); 
    //c2->cd(3); h_ytg->Draw("same"); 
    c2->cd(5); h_ttg->Draw("same"); 
    c2->cd(7); h_ptg->Draw("same"); 

    c2->cd(2);gPad->SetLogy(1);gPad->SetGridy(1);r_dtg->GetYaxis()->SetRangeUser(0.1,10.); r_dtg->Draw("");  
    c2->cd(4);gPad->SetLogy(1);gPad->SetGridy(1);r_ztg->GetYaxis()->SetRangeUser(0.1,10.); r_ztg->Draw("same"); 
    //c2->cd(4);gPad->SetLogy(1);gPad->SetGridy(1);r_ytg->GetYaxis()->SetRangeUser(0.1,10.);r_ytg->Draw(""); 
    c2->cd(6);gPad->SetLogy(1);gPad->SetGridy(1);r_ttg->GetYaxis()->SetRangeUser(0.1,10.); r_ttg->Draw(""); 
    c2->cd(8);gPad->SetLogy(1);gPad->SetGridy(1);r_ptg->GetYaxis()->SetRangeUser(0.1,10.); r_ptg->Draw(""); 

    pic=aPath+"/"  + aTarget+"_"+aKin+"_"+Form("%s_2_tg_%s.png",aArm.Data(), aCom.Data());
    cout<<"      ### Saving plot: "<< pic.Data()<<endl;
    outlog<<"      ### Saving plot: "<< pic.Data()<<endl;
    c2->Print(pic);

    TH1F *r_xbj = (TH1F*) h_xbj->Clone("r_xbj"); r_xbj->Divide(m_xbj);
    r_xbj->SetTitle(Form("x_{bj} Ratio (EX/MC) %s@%s (#%s)",  aTarget.Data(),aKin.Data(),aArm.Data())); 
    r_xbj->SetXTitle("x_{bj}"); r_xbj->SetTitleSize(2.3); r_xbj->GetYaxis()->SetRangeUser(0.1,10.);r_xbj->SetLineColor(1);    

    TCanvas *c3 = new TCanvas("c3","c3 Focal Plane",900,900);
    c3->Clear();
    c3->Divide(1,2);
    
    scale = norm/h_xbj->Integral(); h_xbj->Scale(scale); h_xbj->SetTitle("EX&MC Xbj normalized to 1");
    scale = norm/m_xbj->Integral(); m_xbj->Scale(scale); m_xbj->SetTitle("EX&MC Xbj normalized to 1");
    c3->cd(1); gPad->SetLogy(1); h_xbj->Draw(); m_xbj->Draw("same");
    c3->cd(2); gPad->SetLogy(1); gPad->SetGridy(1); r_xbj->Draw();

    pic=aPath+"/"  + aTarget+"_"+aKin+"_"+Form("%s_4_xbj_%s.png",aArm.Data(), aCom.Data());
    cout<<"      ### Saving plot: "<< pic.Data()<<endl;
    outlog<<"      ### Saving plot: "<< pic.Data()<<endl;
    c3->Print(pic);

    /*}}}*/
    TString outroot =aPath+"/"  + aTarget+"_"+aKin+"_"+Form("%s_%s.root",aArm.Data(), aCom.Data());
    TFile *outf = new TFile(outroot.Data(), "recreate");

    h_xfp->Write(); h_yfp->Write(); h_tfp->Write(); h_pfp->Write();
    m_xfp->Write(); m_yfp->Write(); m_tfp->Write(); m_pfp->Write();
    r_xfp->Write(); r_yfp->Write(); r_tfp->Write(); r_pfp->Write();

    h_dtg->Write(); h_ztg->Write(); h_ytg->Write(); h_ttg->Write(); h_ptg->Write();
    m_dtg->Write(); m_ztg->Write(); m_ytg->Write(); m_ttg->Write(); m_ptg->Write();
    r_dtg->Write(); r_ztg->Write(); r_ytg->Write(); r_ttg->Write(); r_ptg->Write();

    outf->Close();
}
/*}}}*/
