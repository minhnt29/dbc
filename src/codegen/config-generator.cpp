#include "config-generator.h"

void ConfigGenerator::FillHeader(FileWriter& wr, const GenDescriptor_t& gsett)
{
  wr.Append("#pragma once");
  wr.Append("");
  wr.Append("/* include common dbccode configurations */");
  wr.Append("#include <dbccodeconf.h>");
  wr.Append("");
  wr.Append("");
  wr.Append("/* ------------------------------------------------------------------------- *");
  wr.Append("  This define enables using CAN message structs with bit-fielded signals");
  wr.Append("  layout.");
  wr.Append("");
  wr.Append("  Note(!): bit-feild was not tested properly. */");
  wr.Append("");
  wr.Append("/* #define %s */", gsett.usebits_def.c_str());
  wr.Append(2);

  wr.Append("/* ------------------------------------------------------------------------- *");
  wr.Append("  This macro enables using CAN message descriptive struct packing functions");
  wr.Append("  (by default signature of pack function intakes a few simple typed params");
  wr.Append("  for loading data, len, etc). To compile you need to define the struct");
  wr.Append("  __CoderDbcCanFrame_t__ which must have fields:");
  wr.Append("");
  wr.Append("    u32 MsgId (CAN Frame message ID)");
  wr.Append("    u8 DLC (CAN Frame payload length field)");
  wr.Append("    u8 Data[8] (CAN Frame payload data)");
  wr.Append("    u8 IDE (CAN Frame Extended (1) / Standard (0) ID type)");
  wr.Append("");
  wr.Append("  This struct definition have to be placed (or be included) in dbccodeconf.h */");
  wr.Append("");
  wr.Append("/* #define %s */", gsett.usesruct_def.c_str());
  wr.Append(2);

  wr.Append("/* ------------------------------------------------------------------------- *");
  wr.Append("  All the signals which have values of factor != 1 or offset != 0");
  wr.Append("  will be named in message struct with posfix '_ro'. Pack to payload");
  wr.Append("  operations will be made on this signal value as well as unpack from payload.");
  wr.Append("");
  wr.Append("  USE_SIGFLOAT macro makes some difference:");
  wr.Append("");
  wr.Append("  1. All the '_ro' fields will have a pair field with '_phys' postfix.");
  wr.Append("  If only offset != 0 is true then the type of '_phys' signal is the same");
  wr.Append("  as '_ro' signal. In other case the type will be @sigfloat_t which");
  wr.Append("  have to be defined in user dbccodeconf.h");
  wr.Append("");
  wr.Append("  2. In pack function '_ro' signal will be rewritten by '_phys' signal, which");
  wr.Append("  requires from user to use ONLY '_phys' signal for packing frame");
  wr.Append("");
  wr.Append("  3. In unpack function '_phys' signal will be written by '_ro' signal.");
  wr.Append("  User have to use '_phys' signal to read physical value. */");
  wr.Append("");
  wr.Append("#define %s", gsett.usesigfloat_def.c_str());
  wr.Append(2);

  wr.Append("/* ------------------------------------------------------------------------- *");
  wr.Append("  Note(!) that the \"canmonitorutil.h\" must be accessed in include path:");
  wr.Append("");
  wr.Append("  This macro adds:");
  wr.Append("");
  wr.Append("  - monitor field @mon1 to message struct");
  wr.Append("");
  wr.Append("  - capture system tick in unpack function and save value to mon1 field");
  wr.Append("  to provide to user better missing frame detection code. For this case");
  wr.Append("  user must provide function declared in canmonitorutil.h - GetSysTick()");
  wr.Append("  which may return 1ms uptime.");
  wr.Append("");
  wr.Append("  - calling function FMon_***  (from 'fmon' driver) inside unpack function");
  wr.Append("  which is empty by default and have to be filled by user if");
  wr.Append("  tests for DLC, rolling, checksum are necessary */");
  wr.Append("");
  wr.Append("/* #define %s */", gsett.usemon_def.c_str());
  wr.Append(2);

  wr.Append("/* ------------------------------------------------------------------------- *");
  wr.Append("  When monitor using is enabled (%s) and define below", gsett.usemon_def.c_str());
  wr.Append("  uncommented, additional signal will be added to message struct. ***_expt:");
  wr.Append("  expected rolling counter, to perform monitoring rolling counter sequence");
  wr.Append("  automatically (result may be tested in dedicated Fmon_*** function) */");
  wr.Append("");
  wr.Append("/* #define %s */", gsett.useroll_def.c_str());
  wr.Append(2);

  wr.Append("/* ------------------------------------------------------------------------- *");
  wr.Append("  When monitor using is enabled (%s) and define below", gsett.usemon_def.c_str());
  wr.Append("  uncommented, frame checksum signal may be handled automatically.");
  wr.Append("");
  wr.Append("  The signal which may be marked as checksum signal must have substring");
  wr.Append("  with next format:");
  wr.Append("    <Checksum:XOR8:3>");
  wr.Append("");
  wr.Append("  where:");
  wr.Append("");
  wr.Append("  - \"Checksum\": constant marker word");
  wr.Append("");
  wr.Append("  - \"XOR8\": type of method, this text will be passed to GetFrameHash");
  wr.Append("  (canmonitorutil.h) function as is, the best use case is to define 'enum");
  wr.Append("  DbcCanCrcMethods' in canmonitorutil.h file with all possible");
  wr.Append("  checksum algorithms (e.g. XOR8, XOR4 etc)");
  wr.Append("");
  wr.Append("  - \"3\": optional value that will be passed to GetFrameHash as integer value");
  wr.Append("");
  wr.Append("  Function GetFrameHash have to be implemented by user");
  wr.Append("");
  wr.Append("  In pack function checksum signal will be calculated automatically");
  wr.Append("  and loaded to payload");
  wr.Append("");
  wr.Append("  In unpack function checksum signal is checked with calculated.");
  wr.Append("  (result may be tested in dedicated Fmon_*** function). */");
  wr.Append("");
  wr.Append("/* #define %s */", gsett.usecsm_def.c_str());
  wr.Append(2);
  wr.Append("/* ------------------------------------------------------------------------- *");
  wr.Append("  FMon handling model can be build in two ways: ");
  wr.Append("");
  wr.Append("  1 - Default. In this case when specific frame unpack is called the ");
  wr.Append("  specific FMon_{Frame name}_{driver name} functoin will be called.");
  wr.Append("  User's code scope has to define each of these functions. Each function is");
  wr.Append("  responsible for the error handling of one frame");
  wr.Append("");
  wr.Append("  2 - MONO. In this case there is only one function to perform any frame ");
  wr.Append("  monitoring. This function has to be implemented in the user's code scope.");
  wr.Append("  This function is named as FMon_MONO_{driver name}. It takes frame id");
  wr.Append("  which can be used for selection of the logic for a frame monitoring.");
  wr.Append("  This mode costs a bit more in runtime but when you often edit you DBC and you ");
  wr.Append("  have more than one project it could be more maintanable (there is");
  wr.Append("  no necessity to replace source code)");
  wr.Append("");
  wr.Append("  For using MONO way uncomment line below */");
  wr.Append("/* #define %s */", gsett.usemonofmon_def.c_str());

}
