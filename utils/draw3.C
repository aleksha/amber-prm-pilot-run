{

  std::ifstream f1("./v1.tzt"  , std::ios::in);
  std::ifstream f2("./v2.tzt"  , std::ios::in);
  std::ifstream f3("./v3.tzt"  , std::ios::in);

  int ch1, ch2, ch3;
  double val1, val2, val3;

  TH1F* h1 = new TH1F("h1",";time, #mus; ",176,0,0.04*176);
  TH1F* h2 = new TH1F("h2",";time, #mus; ",176,0,0.04*176);
  TH1F* h3 = new TH1F("h3",";time, #mus; ",176,0,0.04*176);

  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h3->SetLineColor(4);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);

  for(int i=0; i<175; i++){
    f1 >> ch1 >> val1;
    f2 >> ch2 >> val2;
    f3 >> ch3 >> val3;

    cout << ch1 << "  " << val1 << "\t\t";
    cout << ch2 << "  " << val2 << "\t\t";
    cout << ch3 << "  " << val3 << "\t\n";

    h1->SetBinContent(ch1+1,val1);
    h2->SetBinContent(ch2+1,val2);
    h3->SetBinContent(ch3+1,val3);
  }

  t1 = TLatex(3, 0.025, "Response func.");
  t2 = TLatex(3, 0.022, "W_{2} = 10.0 mm/#mus");
  t3 = TLatex(3, 0.019, "W_{2} =  7.5 mm/#mus");

  t2.SetTextColor(2);
  t3.SetTextColor(4);

  TCanvas* canv = new TCanvas("canv", "canv", 800,800);
  gStyle->SetOptStat(0);
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");
  t1.Draw("same");
  t2.Draw("same");
  t3.Draw("same");

  canv->Print("different_W2.png");

  f1.close();
  f2.close();
  f3.close();

}
