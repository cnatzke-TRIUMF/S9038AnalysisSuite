#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"

void AnglePlot(){

  // Inputs and Control
  /*
 TString PlotTitle("99hrs 90Sr source vs 48hrs Room BG, no protons");
 TString SrRunName("/data2/S9038/Histograms/Runs_15733-15746-90Sr-no-protons.root");
 TString BgRunName("/data2/S9038/Histograms/Runs_15716-15722-BG-no-protons.root");
 TString SrHistoName("addbackESum_Supp");
 TString SrLegend("90Sr runs 15733-15746");
 TString BgHistoName("addbackESum_Supp");
 TString BgLegend("BG runs 15716-15722");
 int YMax=4000;
  */

 TString PlotTitle("Angular Correlation Plots");
 TString Plot2Title("Background-subtracted Projections");
 // TString SrRunName("/data2/S9038/Histograms/TwoPhotonGriffinAnglePlots15738-15752-90Sr-120hrs.root");
 TString SrRunName("/data2/S9038/Histograms/TwoPhotonGriffinAnglePlots15738-15759.root"); // 200 hrs
 TString BgRunName("/data2/S9038/Histograms/TwoPhotonGriffinAnglePlots15716-15722.root");
 TString Sr1HistoName("AB_AngDiff_Supp_1760-1764");
 TString Sr2HistoName("AB_AngDiff_Supp_1750");
 TString Sr3HistoName("AB_AngDiff_Supp_1780");
 // TString Sr4HistoName("AB_AngDiff_Supp_1140");
 TString BgHistoName("AB_AngDiff_Supp_1764");
 Double_t myZmin=0.;
 Double_t myZmax=280.;

 //Declare and set up the Canvas with 4 pads
 TCanvas *c1 = new TCanvas("c1",PlotTitle,800,650);
c1->Divide(2,2);
TPad* pada = (TPad*)c1->GetPad(1);
TPad* padb = (TPad*)c1->GetPad(2);
TPad* padc = (TPad*)c1->GetPad(3);
TPad* padd = (TPad*)c1->GetPad(4);
  gStyle->SetOptStat(kFALSE);

  // Get the spectra from the Sr source run
TFile f1(SrRunName);
 TH2* hSr1 = 0;
 TH2* hSr2 = 0;
 TH2* hSr3 = 0;
 // TH2* hSr4 = 0;
 f1.GetObject(Sr1HistoName,hSr1); // Native binning is 10 degrees and 2keV per bin.
 f1.GetObject(Sr2HistoName,hSr2); // Native binning is 10 degrees and 2keV per bin.
 f1.GetObject(Sr3HistoName,hSr3); // Native binning is 10 degrees and 2keV per bin.
 // f1.GetObject(Sr4HistoName,hSr4); // Native binning is 10 degrees and 2keV per bin.

// Get the spectra from the background histogram
TFile f2(BgRunName);
 TH2* hBg = 0;
 f2.GetObject(BgHistoName,hBg); // Native binning is 10 degrees and 2keV per bin.


// Pad 1: 1760 and 1764keV region from 90Sr source histogram
c1->cd(1);
 hSr1->RebinY(20); // New binning of 40keV per bin
 hSr1->GetYaxis()->SetRangeUser(0, 1800);
 hSr1->SetTitle("176hrs 90Sr Run: 1760+1764keV");
 hSr1->SetAxisRange(myZmin, myZmax,"Z");
 hSr1->GetYaxis()->SetTitle("Energy of #gamma1 (keV)");
 hSr1->GetYaxis()->CenterTitle();
 hSr1->GetYaxis()->SetTitleOffset(1.5);
 hSr1->Draw("colz");
 pada->Modified();

 // Pad 2: 1764keV from BG run
c1->cd(2);
 hBg->RebinY(20); // New binning of 40keV per bin
 hBg->GetYaxis()->SetRangeUser(0, 1800);
 hBg->Add(hBg,2.); // This is now x3
 hBg->SetTitle("3x 48hrs Background Run: 1764keV");
 hBg->SetAxisRange(myZmin, myZmax,"Z");
 hBg->Draw("colz");
 padb->Modified();

 // Pad 3: 1750 and 1780keV background region from Sr source
c1->cd(3);
 hSr2->RebinY(20); // New binning of 40keV per bin
 hSr2->GetYaxis()->SetRangeUser(0, 1800);
 hSr3->RebinY(20); // New binning of 40keV per bin
 hSr3->GetYaxis()->SetRangeUser(0, 1800);
 hSr2->Add(hSr3,1.);
 hSr2->SetTitle("176hrs 90Sr Run: 1750+1780keV");
 hSr2->SetAxisRange(myZmin, myZmax,"Z");
 hSr2->GetYaxis()->SetTitle("Energy of #gamma1 (keV)");
 hSr2->GetYaxis()->CenterTitle();
 hSr2->GetYaxis()->SetTitleOffset(1.5);
 hSr2->GetXaxis()->SetTitle("Angular Difference (degrees)");
 hSr2->GetXaxis()->CenterTitle();
 hSr2->Draw("colz");
 padc->Modified();

 // Pad 4: Background-subtracted 1760keV region.
 c1->cd(4);
 TH2* hSr4 = (TH2*)hSr1->Clone();
 hSr4->Add(hSr2,-1.0); // Sr2 and Sr3 already summed above
 // hSr4->Add(hBg,-1.0); // Sr run is 200hrs, BG run is 48hrs - Already multipiled above
 hSr4->SetTitle("Background-subtracted 1760keV");
 // hSr4->SetAxisRange(myZmin, myZmax,"Z");
 hSr4->GetXaxis()->SetTitle("Angular Difference (degrees)");
 hSr4->GetXaxis()->CenterTitle();
 hSr4->GetYaxis()->SetTitle("");
 hSr4->Draw("colz");
 padd->Modified();
 
 /*
 // Pad 4: Sr source 1140keV region for PAF.
 c1->cd(4);
 hSr4->RebinY(20); // New binning of 40keV per bin
 hSr4->GetYaxis()->SetRangeUser(0, 1200);
 hSr4->SetTitle("120Hrs 90Sr run: Brems and PAF BG, 1140keV");
 // hSr3->SetAxisRange(myZmin, myZmax,"Z");
 hSr4->GetXaxis()->SetTitle("Angular Difference (degrees)");
 hSr4->GetXaxis()->CenterTitle();
 hSr4->GetYaxis()->SetTitle("");
 hSr4->Draw("colz");
 padd->Modified();
 */

 // Update the canvas
  c1->Update();

  // Make 1D projections of the background subtracted matrix
 //Declare and set up the Canvas with 2 pads
 TCanvas *c2 = new TCanvas("c2",Plot2Title,600,550);
 c2->Divide(1,2);
 TPad* pad2a = (TPad*)c2->GetPad(1);
 TPad* pad2b = (TPad*)c2->GetPad(2);
  gStyle->SetOptStat(kFALSE);


 TH1 * h1X = hSr4->ProjectionX();
 TH1 * h1Y = hSr4->ProjectionY();

c2->cd(1);
// h1X->GetXaxis()->SetRange(1700, 1850);
//  h1X->GetYaxis()->SetRangeUser(0, YMax);
 h1X->SetTitle("176hrs Background-subtracted 1760keV");
 // hSr4->SetAxisRange(myZmin, myZmax,"Z");
 h1X->GetXaxis()->SetTitle("Angular Difference (degrees)");
 h1X->GetXaxis()->CenterTitle();
 h1X->GetYaxis()->SetTitle("Counts per 10 degrees");
 h1X->GetYaxis()->CenterTitle();
  h1X->Draw();
 pad2a->Modified();

c2->cd(2);
// h1Y->GetXaxis()->SetRange(1700, 1850);
//  h1Y->GetYaxis()->SetRangeUser(0, YMax);
// h1Y->Rebin(3.); // Now 120keV per bin
 h1Y->SetTitle("");
 h1Y->GetXaxis()->SetTitle("Energy #gamma1 (keV)");
 h1Y->GetXaxis()->CenterTitle();
 h1Y->GetYaxis()->SetTitle("Counts per 40keV");
 h1Y->GetYaxis()->CenterTitle();
  h1Y->Draw();
 pad2b->Modified();
  c2->Update();



 // Wait for Press any key to continue...
 cin.get();

}
