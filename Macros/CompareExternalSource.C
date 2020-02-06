#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include <fstream>
#include "TString.h"
#include "TFile.h"

// list of files to be read in 
ifstream fin("/data4/S9038/externalSourceList.txt");

void CompareExternalSource(){
   
   TString inputFiles[6];
   TH2D* inputHistograms[6];
   TString HistName("AB_AngDiff_Supp_1332");
   TString CanvasTitle("Comparison of External Source Placements");

   //Declare and set up the Canvas with 4 pads
   TCanvas *c1 = new TCanvas("c1",CanvasTitle,900,600);
   c1->Divide(3,2);
   TPad* pad1 = (TPad*)c1->GetPad(1);
   TPad* pad2 = (TPad*)c1->GetPad(2);
   TPad* pad3 = (TPad*)c1->GetPad(3);
   TPad* pad4 = (TPad*)c1->GetPad(4);
   TPad* pad5 = (TPad*)c1->GetPad(5);
   TPad* pad6 = (TPad*)c1->GetPad(6);
   gStyle->SetOptStat(kFALSE);

   // I want to expand the functionality to create the images in a loop, but
   // I do not know how.

   // read in data files
   cout << "Reading in data files ... " << endl;
   for(int idx=0; idx<6; idx++){
      fin >> inputFiles[idx];
      cout << inputFiles[idx].Data() << endl;
   }
   cout << "Reading in data files ... [DONE]" << endl;

   c1->cd(1);
   TFile* f1 = TFile::Open(inputFiles[0], "read");
   TH2D* h1 = (TH2D*)f1->Get(HistName);
   h1->SetTitle("#theta: 90deg Z: 0in");
   h1->GetYaxis()->SetTitle("Energy of #gamma1 (per 2keV)");
   h1->GetYaxis()->CenterTitle();
   h1->GetYaxis()->SetTitleOffset(1.5);
   h1->GetXaxis()->SetTitle("Angular Difference (per 10 degrees)");
   h1->GetXaxis()->CenterTitle();
   h1->GetYaxis()->SetRangeUser(0,1400);
   h1->GetXaxis()->SetRangeUser(20,180);
   h1->Draw("colz");
   pad1->Modified();

   c1->cd(2);
   TFile* f2 = TFile::Open(inputFiles[1], "read");
   TH2D* h2 = (TH2D*)f2->Get(HistName);
   h2->SetTitle("#theta: 90deg Z: -33in");
   h2->GetYaxis()->SetTitle("Energy of #gamma1 (per 2keV)");
   h2->GetYaxis()->CenterTitle();
   h2->GetYaxis()->SetTitleOffset(1.5);
   h2->GetXaxis()->SetTitle("Angular Difference (per 10 degrees)");
   h2->GetXaxis()->CenterTitle();
   h2->GetYaxis()->SetRangeUser(0,1400);
   h2->GetXaxis()->SetRangeUser(20,180);
   h2->Draw("colz");
   pad2->Modified();

   c1->cd(3);
   TFile* f3 = TFile::Open(inputFiles[2], "read");
   TH2D* h3 = (TH2D*)f3->Get(HistName);
   h3->SetTitle("#theta: 90deg Z: +33in");
   h3->GetYaxis()->SetTitle("Energy of #gamma1 (per 2keV)");
   h3->GetYaxis()->CenterTitle();
   h3->GetYaxis()->SetTitleOffset(1.5);
   h3->GetXaxis()->SetTitle("Angular Difference (per 10 degrees)");
   h3->GetXaxis()->CenterTitle();
   h3->GetYaxis()->SetRangeUser(0,1400);
   h3->GetXaxis()->SetRangeUser(20,180);
   h3->Draw("colz");
   pad3->Modified();

   c1->cd(4);
   TFile* f4 = TFile::Open(inputFiles[3], "read");
   TH2D* h4 = (TH2D*)f4->Get(HistName);
   h4->SetTitle("#theta: 45deg Z: +33in");
   h4->GetYaxis()->SetTitle("Energy of #gamma1 (per 2keV)");
   h4->GetYaxis()->CenterTitle();
   h4->GetYaxis()->SetTitleOffset(1.5);
   h4->GetXaxis()->SetTitle("Angular Difference (per 10 degrees)");
   h4->GetXaxis()->CenterTitle();
   h4->GetYaxis()->SetRangeUser(0,1400);
   h4->GetXaxis()->SetRangeUser(20,180);
   h4->Draw("colz");
   pad4->Modified();

   c1->cd(5);
   TFile* f5 = TFile::Open(inputFiles[4], "read");
   TH2D* h5 = (TH2D*)f5->Get(HistName);
   h5->SetTitle("#theta: 45deg Z: 0in");
   h5->GetYaxis()->SetTitle("Energy of #gamma1 (per 2keV)");
   h5->GetYaxis()->CenterTitle();
   h5->GetYaxis()->SetTitleOffset(1.5);
   h5->GetXaxis()->SetTitle("Angular Difference (per 10 degrees)");
   h5->GetXaxis()->CenterTitle();
   h5->GetYaxis()->SetRangeUser(0,1400);
   h5->GetXaxis()->SetRangeUser(20,180);
   h5->Draw("colz");
   pad5->Modified();

   c1->cd(6);
   TFile* f6 = TFile::Open(inputFiles[5], "read");
   TH2D* h6 = (TH2D*)f6->Get(HistName);
   h6->SetTitle("#theta: 45deg Z: -33in");
   h6->GetYaxis()->SetTitle("Energy of #gamma1 (per 2keV)");
   h6->GetYaxis()->CenterTitle();
   h6->GetYaxis()->SetTitleOffset(1.5);
   h6->GetXaxis()->SetTitle("Angular Difference (per 10 degrees)");
   h6->GetXaxis()->CenterTitle();
   h6->GetYaxis()->SetRangeUser(0,1400);
   h6->GetXaxis()->SetRangeUser(20,180);
   h6->Draw("colz");
   pad6->Modified();

   c1->Update();
   // Wait for Press any key to continue...
   cin.get();
} // end CompareExternalSource
