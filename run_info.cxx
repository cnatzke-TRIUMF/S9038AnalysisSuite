//g++ run_info.cxx -std=c++0x -I$GRSISYS/include -L$GRSISYS/lib `grsi-config --cflags --all-libs --GRSIData-libs` -I$GRSISYS/GRSIData/include -L$GRSISYS/GRSIData/lib `root-config --cflags --libs` -lTreePlayer -lMathMore -lSpectrum -lMinuit -lPyROOT -o RunInfo
#include <iostream>
#include <iomanip>
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TChannel.h"
#include "TParserLibrary.h"
#include "TEnv.h"
#include "TRunInfo.h"

using namespace std;

void runinfo(char const * infile, char const * calfile) {


  TFile * inputfile = new TFile(infile, "READ");
  if (!inputfile->IsOpen()) {
    printf("Opening file failed, aborting\n");
    return;
  }
  TChain * AnalysisTree = (TChain * ) inputfile->Get("AnalysisTree");
  printf("%i tree files, details:\n", AnalysisTree->GetNtrees());
  AnalysisTree->ls();
  TTree * tree = (TTree * ) AnalysisTree->GetTree();
  printf("Reading calibration file: %s\n", calfile);
  TChannel::ReadCalFile(calfile);

  TRunInfo* runinfo = dynamic_cast<TRunInfo*>(inputfile->Get("TRunInfo"));

  string resultfile = "BadRuns.txt";
  ifstream test(resultfile.c_str());
  ofstream ffile;
  if(test.good()) {
    ffile.open(resultfile.c_str(),ios::app);
  }
  else {
    ffile.open(resultfile.c_str());
  }
  string tempstring = infile;
  std::size_t first= tempstring.find_first_of("0123456789");
  std::size_t last= tempstring.find_last_of("0123456789");
  string run = "run";
  string runfile = tempstring.substr(first,(last+1-first));
  string runnumber = tempstring.substr(first,5);
  string subrunnumber = tempstring.substr(last-2,3);
  int rnum = stoi(runnumber);
  int snum = stoi(subrunnumber); 
  run.append(runfile);
  run.append(".mid");
  if((rnum != runinfo->RunNumber()) && (snum != runinfo->SubRunNumber()) ) ffile << run << endl;
  ffile.close();

}

int main(int argc, char ** argv) {

  char const * afile;
  char const * calfile;
  printf("Starting sortcode\n");

  // Input-chain-file, output-histogram-file
  if (argc == 1) {
	  cout << "Insufficient arguments, provide argument tree files" << endl;
	  return 0;
  } else if (argc == 2) {
	  afile = argv[1];
	  calfile = "CalibrationFile.cal";
  } else if (argc == 3) {
	  afile = argv[1];
	  calfile = argv[2];
  }  else if (argc > 3) {
	  printf("Too many arguments\n");
	  return 0;
  }

  printf("Input file:%s\nCalibration file: %s\n", afile, calfile);

  runinfo(afile, calfile);

  return 0;
}
