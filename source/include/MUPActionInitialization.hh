#ifndef MUPActionInitialization_h
#define MUPActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class MUPActionInitialization : public G4VUserActionInitialization
{
  public:
    MUPActionInitialization();
    virtual ~MUPActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif


