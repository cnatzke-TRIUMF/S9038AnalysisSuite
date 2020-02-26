//////////////////////////////////////////////////////////////////////////////////
// This is a macro to update the calibration files of many analysis trees at
// once between run1 and run2.
//
// Run this script in the parent directory of the experiment 
// (e.g. /data4/S9038)
//
// Author:        Connor Natzke (cnatzke@triumf.ca)
// Creation Date: Mon 24 Feb 2020 02:07:23 PM PST
// Last Update:   Mon 24 Feb 2020 02:07:27 PM PST
// Usage:         .x UpdateCalibration.C(run1, run2, calFile)
//
//////////////////////////////////////////////////////////////////////////////////

// Global variables
const char * analysis_tree_path = "/data4/S9038/AnalysisTrees/";

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
 * Updates the calibration in a range of analysis trees
 *
 * @param run_1      First run
 * @param run_2      Second run
 * @param calFile    System path to new calibration file
 ***************************************************************/
void UpdateCalibration(int run1, int run2, TString calFile)
{
   TString cal_file_path = (TString)gSystem->pwd() + '/' + calFile;
   cout << "Using calibration file: " << cal_file_path << "\n" << endl;
   int current_tree = run1;
   while (current_tree <= run2){
      std::cout << "\nProcessing Run " << current_tree << " ... " << std::endl;

      // find all subruns for a given run number
      vector<TString> input_files = ListRunFiles(analysis_tree_path, current_tree);
      cout << "Found " << input_files.size() << " subruns." << endl;
      for (auto const& i : input_files){ // loops through vector 
         TFile *f = TFile::Open(i, "read");
         // file integrity check
         if (!f->IsZombie()) {
            TChannel::ReadCalFile(cal_file_path);
            TChannel::WriteToRoot();
         } else{
         std::cout << "Error opening file: " << i << std::endl;
         std::cout << "Does the file exist?" << std::endl;
         }
         delete f;
      }

      cout << "Processing Run " << current_tree << " ... [DONE]" << endl;
      
      current_tree++;
   } // end current_tree while loop
}

