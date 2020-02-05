//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct 25 13:18:27 2016 by ROOT version 5.34/24
// from TTree FragmentTree/FragmentTree
// found on file: fragment07844_000.root
//////////////////////////////////////////////////////////

#ifndef TwoPhotonGriffinTimingSelector_h
#define TwoPhotonGriffinTimingSelector_h

#include "TChain.h"
#include "TFile.h"

#include "TH1.h"
#include "TH2.h"
#include "THnSparse.h"

// Header file for the classes stored in the TTree if any.
#include "TGriffin.h"
#include "TGriffinBgo.h"
#include "TLaBr.h"
#include "TLaBrBgo.h"
#include "TZeroDegree.h"
#include "TSceptar.h"
#include "TTAC.h"
#include "TDescant.h"
#include "TGRSISelector.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class TwoPhotonGriffinTimingSelector : public TGRSISelector { //Must be same name as .C and .h

    public :
        TGriffin* fGrif; //Pointers to spot that events will be
        TGriffinBgo* fBgo;
        TZeroDegree* fZds;
        TSceptar* fScep;
        TLaBr* fLaBr;
        TLaBrBgo* fLaBrBgo;
        TTAC* fTAC;
        TDescant* fDesc;
        Long64_t fCycleLength;

        TwoPhotonGriffinTimingSelector(TTree * /*tree*/ =0) : TGRSISelector(), fGrif(NULL), fBgo(NULL), fZds(NULL), fScep(NULL), fLaBr(NULL), fLaBrBgo(NULL), fTAC(NULL), fDesc(NULL) {
            SetOutputPrefix("TwoPhotonGriffinTimingPlots"); //Changes prefix of output file
        }
        //These functions are expected to exist
        virtual ~TwoPhotonGriffinTimingSelector() { }
        virtual Int_t   Version() const { return 2; }
        void CreateHistograms();
        void FillHistograms();
        void InitializeBranches(TTree *tree);

        ClassDef(TwoPhotonGriffinTimingSelector,2); //Makes ROOT happier
};

#endif

#ifdef TwoPhotonGriffinTimingSelector_cxx
void TwoPhotonGriffinTimingSelector::InitializeBranches(TTree* tree)
{
    if(!tree) return;
    if(tree->SetBranchAddress("TGriffin", &fGrif) == TTree::kMissingBranch) {
        fGrif = new TGriffin;
    }
    if(tree->SetBranchAddress("TGriffinBgo", &fBgo) == TTree::kMissingBranch) {
        fBgo = new TGriffinBgo;
    }
    if(tree->SetBranchAddress("TLaBr", &fLaBr) == TTree::kMissingBranch) {
        fLaBr = new TLaBr;
    }
    if(tree->SetBranchAddress("TLaBrBgo", &fLaBrBgo) == TTree::kMissingBranch) {
        fLaBrBgo = new TLaBrBgo;
    }
    if(tree->SetBranchAddress("TZeroDegree", &fZds) == TTree::kMissingBranch) {
        fZds = new TZeroDegree;
    }
    if(tree->SetBranchAddress("TSceptar", &fScep) == TTree::kMissingBranch) {
        fScep = new TSceptar;
    }
    if(tree->SetBranchAddress("TTAC", &fTAC) == TTree::kMissingBranch) {
        fTAC = new TTAC;
    }
    if(tree->SetBranchAddress("TDescant", &fDesc) == TTree::kMissingBranch) {
        fDesc = new TDescant;
    }

}

#endif // #ifdef TwoPhotonGriffinTimingSelector_cxx
