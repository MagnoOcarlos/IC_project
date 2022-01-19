{

	auto hChegada0 = new TH1D("hChegada0","Dividing the arrive spectrum by the injection spectrum.", 40, 17,21);
	auto hChegada20 = new TH1D("hChegada30","Angle 10(N=874)", 40, 17,21);
	auto hChegada40 = new TH1D("hChegada90"," Angle 50(N=175)", 40, 17,21);
	auto title = new TH1D("hChegada90"," Dividing the arrive energy spectrum by the injection energy spectrum. ", 40, 17,21);
	

	auto hChegada60 = new TH1D("hChegada0","Dividing the arrive spectrum by the injection spectrum.", 40, 17,21);
	auto hChegada80 = new TH1D("hChegada30","Angle 10(N=874)", 40, 17,21);
	
	auto hSaida0 = new TH1D("hSaida0","Angle 0", 40, 17,21);	
	auto *f = new TF1("f","pow(x,-1)",0.1,1000);


	THStack *hs = new THStack("hs","Dividing the arrive spectrum by the injection spectrum");

	ifstream input0("../100k/ang0.txt");
	ifstream input20("../100k/ang20.txt");
	ifstream input40("../100k/ang40.txt");

	ifstream input60("../100k/ang60.txt");
	ifstream input80("../100k/ang80.txt");


	//Injection Spectrum 
	int nSaida=100000;
	double E=0;

	for(int i=0;i<nSaida;i++){

		E=log10(f->GetRandom()*pow(10,18));
		hSaida0->Fill(E);
	}
	//Arrive Spectrum
	

	for(int i=0; i <=24278;i++){
		
		input0 >>E;
		E=log10(E*pow(10,18));
		hChegada0->Fill(E);
	}

	for(int i=0; i <=3375;i++){
		
		input20 >>E;
		E=log10(E*pow(10,18));
		hChegada20->Fill(E);
	}

	for(int i=0; i <=2440;i++){
		
		input40 >>E;
		E=log10(E*pow(10,18));
		hChegada40->Fill(E);
	}

	for(int i=0; i <=2127;i++){
		
		input60 >>E;
		E=log10(E*pow(10,18));
		hChegada60->Fill(E);
	}

	for(int i=0; i <=2102;i++){
		
		input80 >>E;
		E=log10(E*pow(10,18));
		hChegada80->Fill(E);
	}

	//Normalization
	
	
	

	//Dividing the arrive spectrum by the the injection spectrum
 
	auto *c = new TCanvas("c","ASDJ",200,10,600,400);
	TH1 * h1 = (TH1*)hChegada0->Clone("h1");
	TH1 * h2 = (TH1*)hChegada20->Clone("h2");
	TH1 * h3 = (TH1*)hChegada40->Clone("h3");
	TH1 * h4 = (TH1*)hChegada60->Clone("h4");
	TH1 * h5 = (TH1*)hChegada80->Clone("h5");



 	h1->Divide(hChegada0,hSaida0);	
	h2->Divide(hChegada20,hSaida0);	
	h3->Divide(hChegada40,hSaida0);
	h4->Divide(hChegada60,hSaida0);	
	h5->Divide(hChegada80,hSaida0);
	


	h1->SetLineColor(kRed);
	h1->SetStats(0);
	h1->GetYaxis()->SetRangeUser(1e-4,10);
	h1->GetYaxis()->SetTitle("#frac{h_{arr}}{h_{inj}}");
	h1->GetXaxis()->SetTitle("log(E)");
	h1->Draw("HIST");

	h2->SetLineColor(kGreen);
	h2->SetStats(0);
	h2->Draw("HIST same");

	h3->SetLineColor(kBlue);
	h3->SetStats(0);
	h3->Draw("Hist same");
	
	h4->SetLineColor(kOrange);
	h4->SetStats(0);
	h4->Draw("HIST same");

	h5->SetLineColor(kBlack);
	h5->SetStats(0);
	h5->Draw("Hist same");
	
	
	auto leg = new TLegend(0.2,0.2,.8,.8);
	
	leg->AddEntry(h1, "Angle 0 (N=24278)", "l");
	leg->AddEntry(h2, "Angle 20 (N=3375)","l");
	leg->AddEntry(h3, "Angle 40 (N=2440)","l");
	leg->AddEntry(h4, "Angle 60 (N=2127)","l");
	leg->AddEntry(h5, "Angle 80 (N=2102)","l");


	leg->Draw();

	c->SetLogy();
//	c->BuildLegend();
}
