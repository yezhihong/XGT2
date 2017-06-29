
	/*Ratio{{{*/  
	ofstream outfile(Form("Y_%s_%s_%s.dat",Target0.Data(),Target.Data(),Kin0.Data()));
	outfile << Form("%7s %14s %14s %14s %14s %14s %14s %14s %14s %14s %14s", "Xbj","Ratio","Ratio_Err","Y_EX1","Y_EX_Err1","Y_EX2","Y_EX_Err2", "Y_MC1","Y_MC_Err1","Y_MC2","Y_MC_Err2" )<<endl;

	Int_t Count=0;
	Double_t x1,x2,ep1,ep2,ratio,ratio_mc,err, max;
	vector<Double_t> vEp, vXbj, vXbj_Err,vR, vR_Err,vR_MC, vR_MC_Err;

	Double_t X_Min = 10, X_Max = -10, R_Min = 1000.0, R_Max = -1000.0;
	int i,j; max=-1.0;
	for( i=0;i<N1;i++){
		x1 = vXbj1[i];
		ep1 = vEp1[i];
		for( j=0;j<N2;j++){
			x2 = vXbj2[j];
			ep2 = vEp2[j];
			if(abs(ep1-ep2)<0.0001){
				ratio = factor*vY_EX1[i]/vY_EX2[j];
				err = ratio * sqrt( pow(vY_EX_Err2[j]/vY_EX2[j],2) + pow(vY_EX_Err1[i]/vY_EX1[i],2) );
				ratio_mc = factor*vY_MC1[i]/vY_MC2[j];
				if(ratio>1e-30 && ratio<100.&& (err/ratio)<0.5){
					vEp.push_back(ep1);
					vXbj.push_back(x1);
					vXbj_Err.push_back(0.0);
					vR.push_back(ratio);
					vR_MC.push_back(ratio_mc);
					vR_Err.push_back(err);
					cerr <<Form("-----> Found one: xbj1=%f, xbj2=%f, Y_EX1=%f, Y_EX2=%f,Ratio=%f ",x1,x2,vY_EX1[i],vY_EX2[j],ratio)<<endl;
					outfile << Form("%7.5f %14e %14e %14e %14e %14e %14e %14e %14e %14e %14e", 
							x1,ratio, err, vY_EX1[i], vY_EX_Err1[i], vY_EX2[j], vY_EX_Err2[j], vY_MC1[i], vY_MC_Err1[i], vY_MC2[j], vY_MC_Err2[j] )<<endl;

					if(R_Min > ratio)
						R_Min = ratio;
					if(R_Min > ratio_mc)
						R_Min = ratio_mc;
					if(R_Max < ratio)
						R_Max = ratio;
					//				if(R_Max < ratio_mc)
					//					R_Max = ratio_mc;
					if(X_Min > x1)
						X_Min = x1;
					if(X_Max < x1)
						X_Max = x1;
					Count++;
				}
			}
		}
	}

	//Return the value
	for(int k=0; k<Count; k++){
		aXbj[k] = vXbj[k];
		aR_EX[k] = vR[k];
		aR_EX_Err[k] = vR_Err[k];
		aR_MC[k] = vR_MC[k];
	}
	aN[0] = Count;
	cerr<<"******************** Factor = "<< factor<<endl;
	outfile.close();
	/*}}}*/
