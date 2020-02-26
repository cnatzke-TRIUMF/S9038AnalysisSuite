#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TMath.h"

Float_t gateEnergy = 1140.; //keV
Float_t electronRestMassEnergy = 511.; //keV
Float_t E_kin = gateEnergy - 2 * electronRestMassEnergy; //keV

Double_t paf_energy_dist_gamma1(Double_t *theta, Double_t *par){
   return (par[0] + 2*electronRestMassEnergy)*electronRestMassEnergy/(par[0] + 2*electronRestMassEnergy - TMath::Sqrt(par[0]*(par[0] + 2*electronRestMassEnergy))*TMath::Cos(TMath::Pi()/180 * theta[0]));
}

Double_t paf_energy_dist_gamma2(Double_t *theta, Double_t *par){
   return (par[0] + 2*electronRestMassEnergy)*electronRestMassEnergy/(par[0] + 2*electronRestMassEnergy + TMath::Sqrt(par[0]*(par[0] + 2*electronRestMassEnergy))*TMath::Cos(TMath::Pi()/180. * theta[0]));
}

Double_t paf_energy_max(Float_t kineticEnergy){
   return ((kineticEnergy + 2*electronRestMassEnergy)*electronRestMassEnergy)/(kineticEnergy + 2*electronRestMassEnergy - TMath::Sqrt(kineticEnergy*(kineticEnergy + 2*electronRestMassEnergy)));
}

Double_t paf_energy_min(Float_t kineticEnergy){
   return (kineticEnergy + 2*electronRestMassEnergy)*electronRestMassEnergy/(kineticEnergy + 2*electronRestMassEnergy + TMath::Sqrt(kineticEnergy*(kineticEnergy + 2*electronRestMassEnergy)));
}

Double_t compton_scatter_dist(Double_t *theta, Double_t *par){
   return par[0]/(1 + (par[0]/electronRestMassEnergy) * (1 - TMath::Cos(TMath::Pi() / 180. * (theta[0]))));
}

Double_t compton_scatter_dist_2(Double_t *theta, Double_t *par){
   return par[0] - (par[0]/(1 + (par[0]/electronRestMassEnergy) * (1 - TMath::Cos(TMath::Pi() / 180. * (theta[0])))));
}

void AngleEnergyProjections1140_PAF(){

   // Inputs and Control

   TString PlotTitle("Angular Correlation Plots");
   TString Plot2Title("Background-subtracted Projections");
   // TString SrRunName("/data2/S9038/Histograms/TwoPhotonGriffinAnglePlots15738-15752-90Sr-120hrs.root");
   TString SrRunName("/data4/S9038/Histograms/TwoPhotonGriffinAnglePlots15734-15759-90Sr-200hrs.root"); // 200 hrs
   TString BgRunName("/data4/S9038/Histograms/TwoPhotonGriffinAnglePlots15716-15722.root");
   TString Sr1HistoName("AB_AngDiff_Supp_1760-1764");
   TString Sr2HistoName("AB_AngDiff_Supp_1750");
   TString Sr3HistoName("AB_AngDiff_Supp_1780");
   TString Sr4HistoName("AB_AngDiff_Supp_1140");
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
   TH2* hSr4 = 0;
   f1.GetObject(Sr1HistoName,hSr1); // Native binning is 10 degrees and 2keV per bin.
   f1.GetObject(Sr2HistoName,hSr2); // Native binning is 10 degrees and 2keV per bin.
   f1.GetObject(Sr3HistoName,hSr3); // Native binning is 10 degrees and 2keV per bin.
   f1.GetObject(Sr4HistoName,hSr4); // Native binning is 10 degrees and 2keV per bin.

   // Get the spectra from the background histogram
   TFile f2(BgRunName);
   TH2* hBg = 0;
   TH1* hGam = 0;
   f2.GetObject(BgHistoName,hBg); // Native binning is 10 degrees and 2keV per bin.

   f1.GetObject(GamHistoName,hGam);


   // Pad 1: 1461keV region from background run
   c1->cd(1);
   //hSr4->RebinY(20); // New binning of 40keV per bin
   hSr4->GetYaxis()->SetRangeUser(0, 1200);
   hSr4->SetTitle("200hrs 90Sr Run: 1140keV BG");
   //// hBg->SetAxisRange(myZmin, myZmax,"Z");
   hSr4->GetYaxis()->SetTitle("Energy of #gamma1 (per 40keV)");
   hSr4->GetXaxis()->SetTitle("Angular Difference (per 10 degrees)");

   hSr4->GetYaxis()->CenterTitle();
   hSr4->GetYaxis()->SetTitleOffset(1.5);
   hSr4->GetXaxis()->CenterTitle();
   hSr4->Draw("colz");

   
   // PAF Function
   TF1 *paf_1 = new TF1("paf_energy_1", paf_energy_dist_gamma1, 0, 180, 1);
   paf_1->SetParameter(0, E_kin);
   paf_1->SetParName(0, "E_kin");
   paf_1->SetLineStyle(kDashed);
   paf_1->SetLineColor(kBlack);
   paf_1->Draw("lsame");
   //paf_1->Draw();

   TF1 *paf_2 = new TF1("paf_energy_2", paf_energy_dist_gamma2, 0, 180, 1);
   paf_2->SetParameter(0, E_kin);
   paf_2->SetParName(0, "E_kin");
   paf_2->SetLineStyle(kDashed);
   paf_2->SetLineColor(kBlack);
   paf_2->Draw("lsame");

   TF1 *compton_1 = new TF1("compton_1", compton_scatter_dist, 0, 180, 1);
   compton_1->SetParameter(0, gateEnergy);
   compton_1->SetParName(0, "gateEnergy");
   compton_1->SetLineStyle(kDashed);
   compton_1->SetLineColor(kRed);
   compton_1->Draw("lsame");

   TF1 *compton_2 = new TF1("compton_2", compton_scatter_dist_2, 0, 180, 1);
   compton_2->SetParameter(0, gateEnergy);
   compton_2->SetParName(0, "gateEnergy");
   compton_2->SetLineStyle(kDashed);
   compton_2->SetLineColor(kRed);
   compton_2->Draw("lsame");

   // DEBUG INFO
   //TLine *E_max = new TLine(0, paf_energy_max(E_kin), 180, paf_energy_max(E_kin));
   //E_max->Draw("same");
   //TLine *E_min = new TLine(0, paf_energy_min(E_kin), 180, paf_energy_min(E_kin));
   //E_min->Draw("same");
   //std::cout << "Kin Energy: " << E_kin << std::endl;
   //std::cout << "Max Energy: " << paf_energy_max(E_kin) << std::endl;
   //std::cout << "Min Energy: " << paf_energy_min(E_kin) << std::endl;

   pada->Modified();

   // Pad 2: 1764keV from BG run
   c1->cd(2);

   TH1 * h1X = hSr4->ProjectionX();
   // h1X->GetXaxis()->SetRange(1700, 1850);
   //  h1X->GetYaxis()->SetRangeUser(0, YMax);
   h1X->SetTitle("200hrs 90Sr source, 1140keV BG");
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
   padc->SetLogy();

   hGam->GetXaxis()->SetRange(500, 1500);
   // hGam->GetYaxis()->SetRangeUser(0, YMax);
   hGam->SetTitle("200hrs 90Sr source, 1140keV BG");
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

   TH1 * h1Y = hSr4->ProjectionY();
   // h1Y->GetXaxis()->SetRange(1700, 1850);
   //  h1Y->GetYaxis()->SetRangeUser(0, YMax);
   // h1Y->Rebin(3.); // Now 120keV per bin
   h1Y->SetTitle("200hrs 90Sr source, 1140keV BG");
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
