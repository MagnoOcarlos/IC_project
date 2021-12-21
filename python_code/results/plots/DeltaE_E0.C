{

	auto hChegada0 = new TH1D("hChegada0","", 50, 1e-2,1.1);
	auto hChegada20 = new TH1D("hChegada20","", 50, 1e-2,1.1);
	auto hChegada40 = new TH1D("hChegada40"," ", 50, 1e-2,1.1);
	

	auto hChegada60 = new TH1D("hChegada60","", 50, 1e-2,1.1);
	auto hChegada80 = new TH1D("hChegada80","", 50, 1e-2,1.1);
	
	auto hSaida0 = new TH1D("hSaida0","Angle 0", 40, 17,21);	
	auto *f = new TF1("f","pow(x,-1)",0.1,1000);


	THStack *hs = new THStack("hs","Dividing the arrive spectrum by the injection spectrum");

	ifstream input0("../100k/delta_ang0.txt");
	ifstream input20("../100k/delta_ang20.txt");
	ifstream input40("../100k/delta_ang40.txt");

	ifstream input60("../100k/delta_ang60.txt");
	ifstream input80("../100k/delta_ang80.txt");


	double E=0;

	//Arrive Spectrum
	

	for(int i=0; i <=24278;i++){
		
		input0 >>E;
		hChegada0->Fill(E);
	}

	for(int i=0; i <=3375;i++){
		
		input20 >>E;
		hChegada20->Fill(E);
	}

	for(int i=0; i <=2440;i++){
		
		input40 >>E;
		hChegada40->Fill(E);
	}

	for(int i=0; i <=2127;i++){
		
		input60 >>E;
		hChegada60->Fill(E);
	}

	for(int i=0; i <=2102;i++){
		
		input80 >>E;
		hChegada80->Fill(E);
	}

	//Normalization	
	
	double_t factor =1.;

	hChegada0->Scale(factor/hChegada0->GetEntries());
 	hChegada20->Scale(factor/hChegada20->GetEntries());
	hChegada40->Scale(factor/hChegada40->GetEntries());
	hChegada60->Scale(factor/hChegada60->GetEntries());
	hChegada80->Scale(factor/hChegada80->GetEntries());

	
	

 
	auto *c = new TCanvas("c","ASDJ",200,10,600,400);
	TH1 * h1 = (TH1*)hChegada0->Clone("h1");
	TH1 * h2 = (TH1*)hChegada20->Clone("h2");
	TH1 * h3 = (TH1*)hChegada40->Clone("h3");
	TH1 * h4 = (TH1*)hChegada60->Clone("h4");
	TH1 * h5 = (TH1*)hChegada80->Clone("h5");


	h1->SetLineColor(kRed);
	h1->SetStats(0);
	h1->GetYaxis()->SetRangeUser(1e-5,1e0);
//	h1->GetYaxis()->SetTitle("#frac{h_{arr}}{h_{inj}}");
	h1->GetXaxis()->SetTitle("#frac{#Delta E}{E_{0}}");
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
