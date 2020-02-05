#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"

void AngleEnergyProjections1461(){

  // Inputs and Control

 TString PlotTitle("Angular Correlation Plots");
 TString Plot2Title("Background-subtracted Projections");
 // TString SrRunName("/data2/S9038/Histograms/TwoPhotonGriffinAnglePlots15738-15752-90Sr-120hrs.root");
 TString SrRunName("/data4/S9038/Histograms/TwoPhotonGriffinAnglePlots15738-15759.root"); // 200 hrs
 TString BgRunName("/data4/S9038/Histograms/TwoPhotonGriffinAnglePlots15716-15722.root");
 TString Sr1HistoName("AB_AngDiff_Supp_1760-1764");
 TString Sr2HistoName("AB_AngDiff_Supp_1750");
 TString Sr3HistoName("AB_AngDiff_Supp_1780");
 // TString Sr4HistoName("AB_AngDiff_Supp_1140");
 TString BgHistoName("AB_AngDiff_Supp_1461");
 // TString BgHistoName("AB_AngDiff_Supp_1764");
 TString GamHistoName("addbackESum_Supp");
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
 TH1* hGam = 0;
 f2.GetObject(BgHistoName,hBg); // Native binning is 10 degrees and 2keV per bin.
 f2.GetObject(GamHistoName,hGam);


 // Pad 1: 1461keV region from background run
 c1->cd(1);
 hBg->RebinY(20); // New binning of 40keV per bin
 hBg->GetYaxis()->SetRangeUser(0, 1500);
 hBg->SetTitle("48hrs Background Run: 1461keV");
 // hBg->SetAxisRange(myZmin, myZmax,"Z");
 hBg->GetYaxis()->SetTitle("Energy of #gamma1 (per 40keV)");
 hBg->GetYaxis()->CenterTitle();
 hBg->GetYaxis()->SetTitleOffset(1.5);
 hBg->GetXaxis()->SetTitle("Angular Difference (per 10 degrees)");
 hBg->GetXaxis()->CenterTitle();
 hBg->Draw("colz");
 pada->Modified();

 // Pad 2: 1764keV from BG run
c1->cd(2);


 TH1 * h1X = hBg->ProjectionX();
// h1X->GetXaxis()->SetRange(1700, 1850);
//  h1X->GetYaxis()->SetRangeUser(0, YMax);
 h1X->SetTitle("48hrs background, 1461keV");
 // hSr4->SetAxisRange(myZmin, myZmax,"Z");
 h1X->GetXaxis()->SetTitle("Angular Difference (degrees)");
 h1X->GetXaxis()->CenterTitle();
 h1X->GetXaxis()->SetTitleOffset(1.5);
 h1X->GetYaxis()->SetTitle("Counts per 10 degrees");
 h1X->GetYaxis()->CenterTitle();
 h1X->GetYaxis()->SetTitleOffset(1.5);
  h1X->Draw();
 padb->Modified();

 
 // Pad 3: 1750 and 1780keV background region from Sr source
c1->cd(3);


  hGam->GetXaxis()->SetRange(0, 3000);
  // hGam->GetYaxis()->SetRangeUser(0, YMax);
 hGam->SetTitle("48hrs background, 1461keV");
 hGam->GetXaxis()->SetTitle("Energy (keV)");
 hGam->GetXaxis()->CenterTitle();
 hGam->GetXaxis()->SetTitleOffset(1.5);
 hGam->GetYaxis()->SetTitle("Counts per keV");
 hGam->GetYaxis()->CenterTitle();
 hGam->GetYaxis()->SetTitleOffset(1.5);
  hGam->Draw();
 padc->Modified();
 

 // Pad 4: Background-subtracted 1760keV region.
 c1->cd(4);

 TH1 * h1Y = hBg->ProjectionY();
// h1Y->GetXaxis()->SetRange(1700, 1850);
//  h1Y->GetYaxis()->SetRangeUser(0, YMax);
// h1Y->Rebin(3.); // Now 120keV per bin
 h1Y->SetTitle("48hrs background, 1461keV");
 h1Y->GetXaxis()->SetTitle("Energy #gamma1 (keV)");
 h1Y->GetXaxis()->CenterTitle();
 h1Y->GetXaxis()->SetTitleOffset(1.5);
 h1Y->GetYaxis()->SetTitle("Counts per 40keV");
 h1Y->GetYaxis()->CenterTitle();
 h1Y->GetYaxis()->SetTitleOffset(1.5);
 h1Y->Draw();
 padd->Modified();
 
 // Update the canvas
  c1->Update();

 // Wait for Press any key to continue...
 cin.get();

}
