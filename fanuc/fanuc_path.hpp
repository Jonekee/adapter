
#include "device_datum.hpp"
#include "condition.hpp"
#include "adapter.hpp"
#include "fanuc_axis.hpp"
#include <vector>

class StaticEvent : public Event 
{
public:
  StaticEvent(const char *aName = "") : Event(aName) {}      

  virtual bool unavailable() {
    return false;
  }
};

class FanucPath
{
public:
  FanucPath(Adapter *anAdapter, short aPathNumber);
  ~FanucPath();

  bool configure(unsigned short mFlibhndl);
  bool gatherData(unsigned short mFlibhndl);

protected:
  bool configureAxes(unsigned short mFlibhndl);
  bool configureSpindles(unsigned short mFlibhndl);
  
  bool getToolData(unsigned short aFlibhndl);
  bool getProgramInfo(unsigned short mFlibhndl);
  bool getStatus(unsigned short mFlibhndl);
  bool getHeader(unsigned short aFlibhndl, int aProg);
  bool getAxisData(unsigned short aFlibhndl);
  bool getSpindleData(unsigned short aFlibhndl);

  void getCondition(unsigned short aFlibhndl, long aAlarm);
  Condition *translateAlarmNo(long aNum, int aAxis);


  void addDatum(DeviceDatum &aDatum, const char *aName, const char *aSuffix);

protected:
  bool mConfigured;
  Adapter *mAdapter;
  
  short mPathNumber;

  // Path specific data items
  Execution      mExecution;
  IntEvent       mToolId;
  IntEvent       mToolGroup;
  Event          mProgramName;
  Event          mProgramComment;
  IntEvent       mLine;
  Event          mBlock;
  StaticEvent    mActiveAxes;
  ControllerMode mMode;
  EmergencyStop  mEStop;
  
  Sample         mPathFeedrate;
  PathPosition   mPathPosition;
  Sample         mCommandedFeedrate;

  int            mProgramNum;
  short          mSpindleCount;
  short          mAxisCount;

  bool           mToolManagementEnabled;
  bool           mUseModalToolData;
  
  // Path related conditions
  Condition mServo;
  Condition mComms;
  Condition mLogic;
  Condition mMotion;
  Condition mSystem;

  FanucAxis *mXAxis, *mYAxis, *mZAxis;

  std::vector<FanucAxis*> mAxes;
  std::vector<FanucSpindle*> mSpindles;
};