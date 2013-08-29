/*
	Best set of parameters for the model with f reggeon
	and two soft + hard pomerons.
	
	Model:
	
    	Double_t w_traj = alpha_w0 + alpha_w*t;
    	TComplex Aw = TComplex(0.,1.)*TComplex::Exp( TComplex( 0., -Pi*(w_traj)/2. ) ) * a_w * TMath::Exp( b_w*t ) * TMath::Power( s/s_r0, w_traj );

    	Double_t f_traj = alpha_f0 + alpha_f*t;
    	TComplex Af = TComplex::Exp( TComplex( 0., -Pi*(f_traj)/2. ) ) * a_f * TMath::Exp( b_f*t ) * TMath::Power( s/s_r0, f_traj );

    
    	TComplex A;
    	TComplex exp_term_h(b_h + k_h*TMath::Power(L,p_h), 0.);
    	TComplex exp_term_s(b_s + k_s*TMath::Power(L,p_s), -Pi/2.);
    
    	TComplex alpha_h(alpha_h0 + alpha_h1*t, 0.);
    	TComplex alpha_s(alpha_s0 + alpha_s1*t, 0.);

    	A = a_h * TComplex::Exp(exp_term_h * alpha_h) + a_s * TComplex::Exp(exp_term_s * alpha_s);
    	A += Aw;
    	A += Af;

	Evaluated on a dataset 

	TRangeCondition* condTinRange = new TRangeCondition("ConditionTinRange0.1-8", 0.1, 6.);
    	TRangeCondition* condTinRange1 = new TRangeCondition("ConditionTinRange0.1-8", 0.1, 5.5);
    	TRangeCondition* condTinRange2 = new TRangeCondition("ConditionTinRange0.1-8", 0.3, 3.5);

	CompositeDataset* dataset_dsdtPP = new CompositeDataset( "dsdtPPcombined" );
    	dataset_dsdtPP->getComposite()->addDataset( ppdsdt30 );
    	dataset_dsdtPP->getComposite()->addDataset( ppdsdt44 );
    	dataset_dsdtPP->getComposite()->addDataset( ppdsdt53 );
    	dataset_dsdtPP->getComposite()->addDataset( ppdsdt62 );
    	dataset_dsdtPP->getComposite()->addDataset( ppdsdt7000 );

	Gives
	Chi2 = 1008.62
	Npoints = 476
	NDF  = 462
	Chi2/NDF = 2.18

*/
    std::vector< std::pair< string, double > > ipar(NPARAMS);
//-------------------- Hard and soft pomerons power log, f-reggeon ------------------------//
//--------------------- Secondary reggeons ---------------------------//
    //	w-Reggeon parameters
    ipar[0]  = std::make_pair("a_w", 0.);
    ipar[1]  = std::make_pair("alpha_w0",0.);
    ipar[2]  = std::make_pair("alpha_w",0.);
    ipar[3]  = std::make_pair("b_w",0.);
    //	f-Reggeon parameters
    ipar[4]  = std::make_pair("a_f",28.8358);
    ipar[5]  = std::make_pair("alpha_f0",0.975659);
    ipar[6]  = std::make_pair("alpha_f",0.173279);
    ipar[7]  = std::make_pair("b_f",4.32245);
    //-------------------------Hard pomeron ------------------------------//
    ipar[8]   = std::make_pair("a^(h)",0.68);
    ipar[9]   = std::make_pair("b^(h)",-1.1946);
    ipar[10]  = std::make_pair("\\alpha^(h)_0",2.24753);
    ipar[11]  = std::make_pair("\\alpha^(h)_1",1.00781);
    //------------------------- Soft pomeron ------------------------//
    ipar[12]  = std::make_pair("a^(s)",-0.00192723);
    ipar[13]  = std::make_pair("b^(s)",36.3968);
    ipar[14]  = std::make_pair("\\alpha^(s)_0",0.114327);
    ipar[15]  = std::make_pair("\\alpha^(s)_1",0.00971971);
    
    ipar[16]  = std::make_pair("s_{r0}",3.34647);
    ipar[17]  = std::make_pair("k_h",1.04729);
    ipar[18]  = std::make_pair("p_h",0.82152);
    ipar[19]  = std::make_pair("k_s",6.81972);
    ipar[20]  = std::make_pair("p_s",1.14641);