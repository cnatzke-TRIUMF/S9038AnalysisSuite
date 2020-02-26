{
   TCanvas *canvas = new TCanvas("canvas","canvas");
   canvas->Divide(3,1);

   canvas->cd(1);
   TGraph *g[3];
   Double_t x[10] = {0,1,2,3,4,5,6,7,8,9};
   Double_t y[10] = {1,2,3,4,5,5,4,3,2,1};
   TMultiGraph *mg = new TMultiGraph();

   for (int i=0; i<3; i++) {
      g[i] = new TGraph(10, x, y);
      g[i]->SetMarkerStyle(20);
      g[i]->SetMarkerColor(i+2);
      for (int j=0; j<10; j++) y[j] = y[j]-1;
      mg->Add(g[i]);
   }
   mg->Draw("APL");
   mg->SetTitle("Global title; X Axis; Y Axis");

   canvas->cd(3);
   TText *t3 = new TText(.5,.9,"CHAMBER 3");
   t3->SetTextAlign(22);
   t3->SetTextFont(43);
   t3->SetTextSize(20);
   t3->Draw();
}
