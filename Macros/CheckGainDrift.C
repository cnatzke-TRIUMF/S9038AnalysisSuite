//////////////////////////////////////////////////////////////////////////////////
// This macro checks the energy histograms and fits a peak to check how the
// resolution centroid shifts over time.
//
// Run this script in the parent directory of the experiment 
// (e.g. /data4/S9038)
//
// Author:        Connor Natzke (cnatzke@triumf.ca)
// Creation Date: __date__
// Last Update:   __date__
// Usage:         
//
//////////////////////////////////////////////////////////////////////////////////

// Set-up
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TSystemFile.h"
#include "TSystemDirectory.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"

// GRSISort libraries
#include "TRWPeak.h"

#include <iostream>
using namespace std;


// Global variables
const char * histogram_file_path = "/data4/S9038/Histograms/NoProton90Sr/IndividualRuns/";
vector<double> centroids{};

/************************************************************//**
 * @brief Retrieves all 90Sr runs, main function
 *
 * @param run_1   First run
 * @param run_2   Second run
 ***************************************************************/
int CheckGainDrift(int run1, int run2)
{
   int verbose = 0;
   int peak_of_interest = 1460; // keV
   int current_run = run1;
   while (current_run <= run2){
      std::cout << "\nProcessing Run " << current_run << " ... " << std::endl;

      // find all subruns for a given run number
      vector<TString> input_files = ListRunFiles(histogram_file_path, current_run);
      if (verbose > 0) cout << "Found " << input_files.size() << " files." << endl;
      for (auto const& i : input_files){ // loops through vector 
         TFile *f = TFile::Open(i, "read");
         // file integrity check
         if (!f->IsZombie()) {
            // processing here 
            DrawHistograms(f, "griffinE", peak_of_interest);
         } else{
         std::cout << "Error opening file: " << i << std::endl;
         std::cout << "Does " << i << " exist?" << std::endl;
         }
         delete f;
      }

      cout << "Processing Run " << current_run << " ... [DONE]" << endl;
      
      current_run++;
   } // end current_run while loop

   for (auto const& i : centroids){ // loops through vector 
      cout << "Found centroid at: " << i << endl;
   }
   
   // Cleaning up
   centroids.clear();

   return 0;
}

/************************************************************//**
 * Lists all of the files in a directory matching the run number
 * (i.e. extracts all subruns for processing)
 *
 * @param dir_name   Directory name 
 * @param ext        Extension of the files (default = ".root")
 ***************************************************************/
vector<TString> ListRunFiles(const char * dir_name, int run_num, const char *ext = ".root"){

   // Setup
   vector<TString> subrun_files;
   int verbose = 0;

   // Converts run number into string
   TString run_number;
   run_number.Form("%d", run_num);

   TSystemDirectory dir(dir_name, dir_name);
   TList* files = dir.GetListOfFiles();
   if (files){
      TSystemFile* file;
      TString fname;
      TIter next(files);
      while ((file=(TSystemFile*)next())){
         fname = file->GetName();
         if (!file->IsDirectory() && fname.EndsWith(ext) && fname.Contains(run_number)){
               if (verbose > 0) cout << dir_name + fname << endl;
               subrun_files.push_back(dir_name + fname);
         }
      }
      delete file;
   }
   delete files;
   if (verbose > 0) cout << "Found " << subrun_files.size() << " subruns. (Safety Check)" << endl;

   return subrun_files;
}

/************************************************************//**
 * @brief Draws histogram
 *
 * @param tFile Name of input TFile
 * @param histName  Name of the histogram
 ***************************************************************/
int DrawHistograms(TFile * tFile, TString histName, int peak){
   int y_min = peak - 100;
   int y_max = peak + 100;

   int fitting_range = 15;
   int x_min = peak - fitting_range;
   int x_max = peak + fitting_range;

   TCanvas *c1 = new TCanvas("c1","c1",960,540);
   c1->Divide(2,2);
   //TPad* pada = (TPad*)c1->GetPad(1); 
   gSystem->ProcessEvents();
   //c1->SetLogz();

   // Retrieving full histogram
   TH2D *h = dynamic_cast<TH2D*>(tFile->Get(histName));
   gStyle->SetOptStat(kFALSE); // removes stats from plot
   h->GetYaxis()->SetRangeUser(y_min, y_max);

   // Setting up projections
   TH1D* full_projection = dynamic_cast<TH1D*>(h->ProjectionY());
   TH1D* match_channel = dynamic_cast<TH1D*>(h->ProjectionY("match_channel", 41, 41)); // channel with consistent gain
   TH1D* drift_channel = dynamic_cast<TH1D*>(h->ProjectionY("drift_channel", 44, 44)); // channel showing gain drift

   // Draw full histogram
   c1->cd(1);
   h->SetTitle("Full Projection;Channel;Energy [keV]");
   h->Draw("colz");
   
   // Draw projection
   c1->cd(2);
   full_projection->SetTitle("Projection of all channels; Energy [keV]; Counts");
   full_projection->Draw();

   // Draw "good" channel
   c1->cd(3);
   match_channel->SetTitle("Consistent Gain Channel (42)");
   match_channel->Draw();

   // Draw "bad" channel
   c1->cd(4);
   drift_channel->SetTitle("Drifting Gain Channel (44)");
   drift_channel->Draw();

   TPeakFitter* pf = new TPeakFitter(x_min, x_max);
   TRWPeak* p1 = new TRWPeak(peak);
   pf->AddPeak(p1);
   pf->Fit(drift_channel, "L");
   double centroid = p1->GetFitFunction()->GetParameter(1);
   centroids.push_back(centroid); // Storing centroid for later use

   // Waits for user input
   c1->Update();
   cin.get();

   // cleaning up
   delete c1; 
   delete h;
   delete full_projection;
   delete pf;
   delete p1;
   delete match_channel;
   delete drift_channel;
   gSystem->ProcessEvents(); // required to keep ROOT from seg-faulting
   return 0;
}

/************************************************************//**
 * @brief Fits specified peak in given spectrum
 *
 * @param tFile Name of input TFile
 * @param histName  Name of the histogram
 * @param peak  centroid of peak (keV)
 ***************************************************************/
int FitPeak(TFile * tFile, TString histName, int peak){

   return 0;
} // End FitPeak

