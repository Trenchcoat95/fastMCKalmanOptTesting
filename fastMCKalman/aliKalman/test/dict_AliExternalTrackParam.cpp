// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dict_AliExternalTrackParam
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "AliVMisc.h"
#include "AliVParticle.h"
#include "AliVTrack.h"
#include "AliVVertex.h"
#include "TStatToolkit.h"
#include "AliTMinuitToolkit.h"
#include "AliPDG.h"
#include "AliPID.h"
#include "AliDrawStyle.h"
#include "AliSysInfo.h"
#include "AliXRDPROOFtoolkit.h"
#include "TTreeStream.h"
#include "AliLog.h"
#include "AliExternalTrackParam.h"

// Header files passed via #pragma extra_include

namespace TStatToolkit {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *TStatToolkit_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("TStatToolkit", 0 /*version*/, "TStatToolkit.h", 54,
                     ::ROOT::Internal::DefineBehavior((void*)0,(void*)0),
                     &TStatToolkit_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *TStatToolkit_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static void delete_AliVParticle(void *p);
   static void deleteArray_AliVParticle(void *p);
   static void destruct_AliVParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliVParticle*)
   {
      ::AliVParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliVParticle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliVParticle", ::AliVParticle::Class_Version(), "AliVParticle.h", 28,
                  typeid(::AliVParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliVParticle::Dictionary, isa_proxy, 4,
                  sizeof(::AliVParticle) );
      instance.SetDelete(&delete_AliVParticle);
      instance.SetDeleteArray(&deleteArray_AliVParticle);
      instance.SetDestructor(&destruct_AliVParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliVParticle*)
   {
      return GenerateInitInstanceLocal((::AliVParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliVParticle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AliPID(void *p = 0);
   static void *newArray_AliPID(Long_t size, void *p);
   static void delete_AliPID(void *p);
   static void deleteArray_AliPID(void *p);
   static void destruct_AliPID(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliPID*)
   {
      ::AliPID *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliPID >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliPID", ::AliPID::Class_Version(), "AliPID.h", 19,
                  typeid(::AliPID), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliPID::Dictionary, isa_proxy, 4,
                  sizeof(::AliPID) );
      instance.SetNew(&new_AliPID);
      instance.SetNewArray(&newArray_AliPID);
      instance.SetDelete(&delete_AliPID);
      instance.SetDeleteArray(&deleteArray_AliPID);
      instance.SetDestructor(&destruct_AliPID);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliPID*)
   {
      return GenerateInitInstanceLocal((::AliPID*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliPID*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_AliVTrack(void *p);
   static void deleteArray_AliVTrack(void *p);
   static void destruct_AliVTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliVTrack*)
   {
      ::AliVTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliVTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliVTrack", ::AliVTrack::Class_Version(), "AliVTrack.h", 27,
                  typeid(::AliVTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliVTrack::Dictionary, isa_proxy, 4,
                  sizeof(::AliVTrack) );
      instance.SetDelete(&delete_AliVTrack);
      instance.SetDeleteArray(&deleteArray_AliVTrack);
      instance.SetDestructor(&destruct_AliVTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliVTrack*)
   {
      return GenerateInitInstanceLocal((::AliVTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliVTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_AliVVertex(void *p);
   static void deleteArray_AliVVertex(void *p);
   static void destruct_AliVVertex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliVVertex*)
   {
      ::AliVVertex *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliVVertex >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliVVertex", ::AliVVertex::Class_Version(), "AliVVertex.h", 13,
                  typeid(::AliVVertex), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliVVertex::Dictionary, isa_proxy, 4,
                  sizeof(::AliVVertex) );
      instance.SetDelete(&delete_AliVVertex);
      instance.SetDeleteArray(&deleteArray_AliVVertex);
      instance.SetDestructor(&destruct_AliVVertex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliVVertex*)
   {
      return GenerateInitInstanceLocal((::AliVVertex*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliVVertex*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TTreeDataElement(void *p);
   static void deleteArray_TTreeDataElement(void *p);
   static void destruct_TTreeDataElement(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTreeDataElement*)
   {
      ::TTreeDataElement *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTreeDataElement >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTreeDataElement", ::TTreeDataElement::Class_Version(), "TTreeStream.h", 16,
                  typeid(::TTreeDataElement), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTreeDataElement::Dictionary, isa_proxy, 4,
                  sizeof(::TTreeDataElement) );
      instance.SetDelete(&delete_TTreeDataElement);
      instance.SetDeleteArray(&deleteArray_TTreeDataElement);
      instance.SetDestructor(&destruct_TTreeDataElement);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTreeDataElement*)
   {
      return GenerateInitInstanceLocal((::TTreeDataElement*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TTreeDataElement*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TTreeStream(void *p);
   static void deleteArray_TTreeStream(void *p);
   static void destruct_TTreeStream(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTreeStream*)
   {
      ::TTreeStream *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTreeStream >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTreeStream", ::TTreeStream::Class_Version(), "TTreeStream.h", 36,
                  typeid(::TTreeStream), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTreeStream::Dictionary, isa_proxy, 4,
                  sizeof(::TTreeStream) );
      instance.SetDelete(&delete_TTreeStream);
      instance.SetDeleteArray(&deleteArray_TTreeStream);
      instance.SetDestructor(&destruct_TTreeStream);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTreeStream*)
   {
      return GenerateInitInstanceLocal((::TTreeStream*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TTreeStream*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TTreeSRedirector(void *p = 0);
   static void *newArray_TTreeSRedirector(Long_t size, void *p);
   static void delete_TTreeSRedirector(void *p);
   static void deleteArray_TTreeSRedirector(void *p);
   static void destruct_TTreeSRedirector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTreeSRedirector*)
   {
      ::TTreeSRedirector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTreeSRedirector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTreeSRedirector", ::TTreeSRedirector::Class_Version(), "TTreeStream.h", 85,
                  typeid(::TTreeSRedirector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTreeSRedirector::Dictionary, isa_proxy, 4,
                  sizeof(::TTreeSRedirector) );
      instance.SetNew(&new_TTreeSRedirector);
      instance.SetNewArray(&newArray_TTreeSRedirector);
      instance.SetDelete(&delete_TTreeSRedirector);
      instance.SetDeleteArray(&deleteArray_TTreeSRedirector);
      instance.SetDestructor(&destruct_TTreeSRedirector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTreeSRedirector*)
   {
      return GenerateInitInstanceLocal((::TTreeSRedirector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TTreeSRedirector*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AliTMinuitToolkit(void *p = 0);
   static void *newArray_AliTMinuitToolkit(Long_t size, void *p);
   static void delete_AliTMinuitToolkit(void *p);
   static void deleteArray_AliTMinuitToolkit(void *p);
   static void destruct_AliTMinuitToolkit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliTMinuitToolkit*)
   {
      ::AliTMinuitToolkit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliTMinuitToolkit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliTMinuitToolkit", ::AliTMinuitToolkit::Class_Version(), "AliTMinuitToolkit.h", 104,
                  typeid(::AliTMinuitToolkit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliTMinuitToolkit::Dictionary, isa_proxy, 4,
                  sizeof(::AliTMinuitToolkit) );
      instance.SetNew(&new_AliTMinuitToolkit);
      instance.SetNewArray(&newArray_AliTMinuitToolkit);
      instance.SetDelete(&delete_AliTMinuitToolkit);
      instance.SetDeleteArray(&deleteArray_AliTMinuitToolkit);
      instance.SetDestructor(&destruct_AliTMinuitToolkit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliTMinuitToolkit*)
   {
      return GenerateInitInstanceLocal((::AliTMinuitToolkit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliTMinuitToolkit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AliPDG(void *p = 0);
   static void *newArray_AliPDG(Long_t size, void *p);
   static void delete_AliPDG(void *p);
   static void deleteArray_AliPDG(void *p);
   static void destruct_AliPDG(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliPDG*)
   {
      ::AliPDG *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliPDG >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliPDG", ::AliPDG::Class_Version(), "AliPDG.h", 14,
                  typeid(::AliPDG), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliPDG::Dictionary, isa_proxy, 4,
                  sizeof(::AliPDG) );
      instance.SetNew(&new_AliPDG);
      instance.SetNewArray(&newArray_AliPDG);
      instance.SetDelete(&delete_AliPDG);
      instance.SetDeleteArray(&deleteArray_AliPDG);
      instance.SetDestructor(&destruct_AliPDG);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliPDG*)
   {
      return GenerateInitInstanceLocal((::AliPDG*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliPDG*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AliDrawStyle(void *p = 0);
   static void *newArray_AliDrawStyle(Long_t size, void *p);
   static void delete_AliDrawStyle(void *p);
   static void deleteArray_AliDrawStyle(void *p);
   static void destruct_AliDrawStyle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliDrawStyle*)
   {
      ::AliDrawStyle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliDrawStyle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliDrawStyle", ::AliDrawStyle::Class_Version(), "AliDrawStyle.h", 259,
                  typeid(::AliDrawStyle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliDrawStyle::Dictionary, isa_proxy, 4,
                  sizeof(::AliDrawStyle) );
      instance.SetNew(&new_AliDrawStyle);
      instance.SetNewArray(&newArray_AliDrawStyle);
      instance.SetDelete(&delete_AliDrawStyle);
      instance.SetDeleteArray(&deleteArray_AliDrawStyle);
      instance.SetDestructor(&destruct_AliDrawStyle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliDrawStyle*)
   {
      return GenerateInitInstanceLocal((::AliDrawStyle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliDrawStyle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AliSysInfo(void *p = 0);
   static void *newArray_AliSysInfo(Long_t size, void *p);
   static void delete_AliSysInfo(void *p);
   static void deleteArray_AliSysInfo(void *p);
   static void destruct_AliSysInfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliSysInfo*)
   {
      ::AliSysInfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliSysInfo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliSysInfo", ::AliSysInfo::Class_Version(), "AliSysInfo.h", 14,
                  typeid(::AliSysInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliSysInfo::Dictionary, isa_proxy, 4,
                  sizeof(::AliSysInfo) );
      instance.SetNew(&new_AliSysInfo);
      instance.SetNewArray(&newArray_AliSysInfo);
      instance.SetDelete(&delete_AliSysInfo);
      instance.SetDeleteArray(&deleteArray_AliSysInfo);
      instance.SetDestructor(&destruct_AliSysInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliSysInfo*)
   {
      return GenerateInitInstanceLocal((::AliSysInfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliSysInfo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AliXRDPROOFtoolkit(void *p = 0);
   static void *newArray_AliXRDPROOFtoolkit(Long_t size, void *p);
   static void delete_AliXRDPROOFtoolkit(void *p);
   static void deleteArray_AliXRDPROOFtoolkit(void *p);
   static void destruct_AliXRDPROOFtoolkit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliXRDPROOFtoolkit*)
   {
      ::AliXRDPROOFtoolkit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliXRDPROOFtoolkit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliXRDPROOFtoolkit", ::AliXRDPROOFtoolkit::Class_Version(), "AliXRDPROOFtoolkit.h", 15,
                  typeid(::AliXRDPROOFtoolkit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliXRDPROOFtoolkit::Dictionary, isa_proxy, 4,
                  sizeof(::AliXRDPROOFtoolkit) );
      instance.SetNew(&new_AliXRDPROOFtoolkit);
      instance.SetNewArray(&newArray_AliXRDPROOFtoolkit);
      instance.SetDelete(&delete_AliXRDPROOFtoolkit);
      instance.SetDeleteArray(&deleteArray_AliXRDPROOFtoolkit);
      instance.SetDestructor(&destruct_AliXRDPROOFtoolkit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliXRDPROOFtoolkit*)
   {
      return GenerateInitInstanceLocal((::AliXRDPROOFtoolkit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliXRDPROOFtoolkit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliLog*)
   {
      ::AliLog *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliLog >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliLog", ::AliLog::Class_Version(), "AliLog.h", 27,
                  typeid(::AliLog), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliLog::Dictionary, isa_proxy, 4,
                  sizeof(::AliLog) );
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliLog*)
   {
      return GenerateInitInstanceLocal((::AliLog*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliLog*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_AliExternalTrackParam(void *p = 0);
   static void *newArray_AliExternalTrackParam(Long_t size, void *p);
   static void delete_AliExternalTrackParam(void *p);
   static void deleteArray_AliExternalTrackParam(void *p);
   static void destruct_AliExternalTrackParam(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliExternalTrackParam*)
   {
      ::AliExternalTrackParam *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliExternalTrackParam >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliExternalTrackParam", ::AliExternalTrackParam::Class_Version(), "AliExternalTrackParam.h", 37,
                  typeid(::AliExternalTrackParam), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliExternalTrackParam::Dictionary, isa_proxy, 4,
                  sizeof(::AliExternalTrackParam) );
      instance.SetNew(&new_AliExternalTrackParam);
      instance.SetNewArray(&newArray_AliExternalTrackParam);
      instance.SetDelete(&delete_AliExternalTrackParam);
      instance.SetDeleteArray(&deleteArray_AliExternalTrackParam);
      instance.SetDestructor(&destruct_AliExternalTrackParam);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliExternalTrackParam*)
   {
      return GenerateInitInstanceLocal((::AliExternalTrackParam*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliExternalTrackParam*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr AliVParticle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliVParticle::Class_Name()
{
   return "AliVParticle";
}

//______________________________________________________________________________
const char *AliVParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliVParticle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliVParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliVParticle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliVParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliVParticle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliVParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliVParticle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AliPID::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliPID::Class_Name()
{
   return "AliPID";
}

//______________________________________________________________________________
const char *AliPID::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliPID*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliPID::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliPID*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliPID::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliPID*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliPID::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliPID*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AliVTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliVTrack::Class_Name()
{
   return "AliVTrack";
}

//______________________________________________________________________________
const char *AliVTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliVTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliVTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliVTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliVTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliVTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliVTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliVTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AliVVertex::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliVVertex::Class_Name()
{
   return "AliVVertex";
}

//______________________________________________________________________________
const char *AliVVertex::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliVVertex*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliVVertex::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliVVertex*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliVVertex::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliVVertex*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliVVertex::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliVVertex*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TTreeDataElement::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TTreeDataElement::Class_Name()
{
   return "TTreeDataElement";
}

//______________________________________________________________________________
const char *TTreeDataElement::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTreeDataElement*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TTreeDataElement::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTreeDataElement*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TTreeDataElement::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTreeDataElement*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TTreeDataElement::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTreeDataElement*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TTreeStream::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TTreeStream::Class_Name()
{
   return "TTreeStream";
}

//______________________________________________________________________________
const char *TTreeStream::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTreeStream*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TTreeStream::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTreeStream*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TTreeStream::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTreeStream*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TTreeStream::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTreeStream*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TTreeSRedirector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TTreeSRedirector::Class_Name()
{
   return "TTreeSRedirector";
}

//______________________________________________________________________________
const char *TTreeSRedirector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTreeSRedirector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TTreeSRedirector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTreeSRedirector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TTreeSRedirector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTreeSRedirector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TTreeSRedirector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTreeSRedirector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AliTMinuitToolkit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliTMinuitToolkit::Class_Name()
{
   return "AliTMinuitToolkit";
}

//______________________________________________________________________________
const char *AliTMinuitToolkit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliTMinuitToolkit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliTMinuitToolkit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliTMinuitToolkit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliTMinuitToolkit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliTMinuitToolkit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliTMinuitToolkit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliTMinuitToolkit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AliPDG::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliPDG::Class_Name()
{
   return "AliPDG";
}

//______________________________________________________________________________
const char *AliPDG::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliPDG*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliPDG::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliPDG*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliPDG::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliPDG*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliPDG::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliPDG*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AliDrawStyle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliDrawStyle::Class_Name()
{
   return "AliDrawStyle";
}

//______________________________________________________________________________
const char *AliDrawStyle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliDrawStyle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliDrawStyle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliDrawStyle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliDrawStyle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliDrawStyle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliDrawStyle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliDrawStyle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AliSysInfo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliSysInfo::Class_Name()
{
   return "AliSysInfo";
}

//______________________________________________________________________________
const char *AliSysInfo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliSysInfo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliSysInfo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliSysInfo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliSysInfo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliSysInfo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliSysInfo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliSysInfo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AliXRDPROOFtoolkit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliXRDPROOFtoolkit::Class_Name()
{
   return "AliXRDPROOFtoolkit";
}

//______________________________________________________________________________
const char *AliXRDPROOFtoolkit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliXRDPROOFtoolkit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliXRDPROOFtoolkit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliXRDPROOFtoolkit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliXRDPROOFtoolkit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliXRDPROOFtoolkit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliXRDPROOFtoolkit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliXRDPROOFtoolkit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AliLog::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliLog::Class_Name()
{
   return "AliLog";
}

//______________________________________________________________________________
const char *AliLog::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliLog*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliLog::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliLog*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliLog::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliLog*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliLog::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliLog*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr AliExternalTrackParam::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliExternalTrackParam::Class_Name()
{
   return "AliExternalTrackParam";
}

//______________________________________________________________________________
const char *AliExternalTrackParam::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliExternalTrackParam*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliExternalTrackParam::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliExternalTrackParam*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliExternalTrackParam::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliExternalTrackParam*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliExternalTrackParam::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliExternalTrackParam*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void AliVParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliVParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliVParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliVParticle::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_AliVParticle(void *p) {
      delete ((::AliVParticle*)p);
   }
   static void deleteArray_AliVParticle(void *p) {
      delete [] ((::AliVParticle*)p);
   }
   static void destruct_AliVParticle(void *p) {
      typedef ::AliVParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliVParticle

//______________________________________________________________________________
void AliPID::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliPID.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliPID::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliPID::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AliPID(void *p) {
      return  p ? new(p) ::AliPID : new ::AliPID;
   }
   static void *newArray_AliPID(Long_t nElements, void *p) {
      return p ? new(p) ::AliPID[nElements] : new ::AliPID[nElements];
   }
   // Wrapper around operator delete
   static void delete_AliPID(void *p) {
      delete ((::AliPID*)p);
   }
   static void deleteArray_AliPID(void *p) {
      delete [] ((::AliPID*)p);
   }
   static void destruct_AliPID(void *p) {
      typedef ::AliPID current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliPID

//______________________________________________________________________________
void AliVTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliVTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliVTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliVTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_AliVTrack(void *p) {
      delete ((::AliVTrack*)p);
   }
   static void deleteArray_AliVTrack(void *p) {
      delete [] ((::AliVTrack*)p);
   }
   static void destruct_AliVTrack(void *p) {
      typedef ::AliVTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliVTrack

//______________________________________________________________________________
void AliVVertex::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliVVertex.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliVVertex::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliVVertex::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_AliVVertex(void *p) {
      delete ((::AliVVertex*)p);
   }
   static void deleteArray_AliVVertex(void *p) {
      delete [] ((::AliVVertex*)p);
   }
   static void destruct_AliVVertex(void *p) {
      typedef ::AliVVertex current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliVVertex

//______________________________________________________________________________
void TTreeDataElement::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTreeDataElement.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTreeDataElement::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTreeDataElement::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TTreeDataElement(void *p) {
      delete ((::TTreeDataElement*)p);
   }
   static void deleteArray_TTreeDataElement(void *p) {
      delete [] ((::TTreeDataElement*)p);
   }
   static void destruct_TTreeDataElement(void *p) {
      typedef ::TTreeDataElement current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTreeDataElement

//______________________________________________________________________________
void TTreeStream::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTreeStream.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTreeStream::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTreeStream::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TTreeStream(void *p) {
      delete ((::TTreeStream*)p);
   }
   static void deleteArray_TTreeStream(void *p) {
      delete [] ((::TTreeStream*)p);
   }
   static void destruct_TTreeStream(void *p) {
      typedef ::TTreeStream current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTreeStream

//______________________________________________________________________________
void TTreeSRedirector::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTreeSRedirector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTreeSRedirector::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTreeSRedirector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TTreeSRedirector(void *p) {
      return  p ? new(p) ::TTreeSRedirector : new ::TTreeSRedirector;
   }
   static void *newArray_TTreeSRedirector(Long_t nElements, void *p) {
      return p ? new(p) ::TTreeSRedirector[nElements] : new ::TTreeSRedirector[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTreeSRedirector(void *p) {
      delete ((::TTreeSRedirector*)p);
   }
   static void deleteArray_TTreeSRedirector(void *p) {
      delete [] ((::TTreeSRedirector*)p);
   }
   static void destruct_TTreeSRedirector(void *p) {
      typedef ::TTreeSRedirector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTreeSRedirector

//______________________________________________________________________________
void AliTMinuitToolkit::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliTMinuitToolkit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliTMinuitToolkit::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliTMinuitToolkit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AliTMinuitToolkit(void *p) {
      return  p ? new(p) ::AliTMinuitToolkit : new ::AliTMinuitToolkit;
   }
   static void *newArray_AliTMinuitToolkit(Long_t nElements, void *p) {
      return p ? new(p) ::AliTMinuitToolkit[nElements] : new ::AliTMinuitToolkit[nElements];
   }
   // Wrapper around operator delete
   static void delete_AliTMinuitToolkit(void *p) {
      delete ((::AliTMinuitToolkit*)p);
   }
   static void deleteArray_AliTMinuitToolkit(void *p) {
      delete [] ((::AliTMinuitToolkit*)p);
   }
   static void destruct_AliTMinuitToolkit(void *p) {
      typedef ::AliTMinuitToolkit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliTMinuitToolkit

//______________________________________________________________________________
void AliPDG::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliPDG.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliPDG::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliPDG::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AliPDG(void *p) {
      return  p ? new(p) ::AliPDG : new ::AliPDG;
   }
   static void *newArray_AliPDG(Long_t nElements, void *p) {
      return p ? new(p) ::AliPDG[nElements] : new ::AliPDG[nElements];
   }
   // Wrapper around operator delete
   static void delete_AliPDG(void *p) {
      delete ((::AliPDG*)p);
   }
   static void deleteArray_AliPDG(void *p) {
      delete [] ((::AliPDG*)p);
   }
   static void destruct_AliPDG(void *p) {
      typedef ::AliPDG current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliPDG

//______________________________________________________________________________
void AliDrawStyle::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliDrawStyle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliDrawStyle::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliDrawStyle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AliDrawStyle(void *p) {
      return  p ? new(p) ::AliDrawStyle : new ::AliDrawStyle;
   }
   static void *newArray_AliDrawStyle(Long_t nElements, void *p) {
      return p ? new(p) ::AliDrawStyle[nElements] : new ::AliDrawStyle[nElements];
   }
   // Wrapper around operator delete
   static void delete_AliDrawStyle(void *p) {
      delete ((::AliDrawStyle*)p);
   }
   static void deleteArray_AliDrawStyle(void *p) {
      delete [] ((::AliDrawStyle*)p);
   }
   static void destruct_AliDrawStyle(void *p) {
      typedef ::AliDrawStyle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliDrawStyle

//______________________________________________________________________________
void AliSysInfo::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliSysInfo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliSysInfo::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliSysInfo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AliSysInfo(void *p) {
      return  p ? new(p) ::AliSysInfo : new ::AliSysInfo;
   }
   static void *newArray_AliSysInfo(Long_t nElements, void *p) {
      return p ? new(p) ::AliSysInfo[nElements] : new ::AliSysInfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_AliSysInfo(void *p) {
      delete ((::AliSysInfo*)p);
   }
   static void deleteArray_AliSysInfo(void *p) {
      delete [] ((::AliSysInfo*)p);
   }
   static void destruct_AliSysInfo(void *p) {
      typedef ::AliSysInfo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliSysInfo

//______________________________________________________________________________
void AliXRDPROOFtoolkit::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliXRDPROOFtoolkit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliXRDPROOFtoolkit::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliXRDPROOFtoolkit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AliXRDPROOFtoolkit(void *p) {
      return  p ? new(p) ::AliXRDPROOFtoolkit : new ::AliXRDPROOFtoolkit;
   }
   static void *newArray_AliXRDPROOFtoolkit(Long_t nElements, void *p) {
      return p ? new(p) ::AliXRDPROOFtoolkit[nElements] : new ::AliXRDPROOFtoolkit[nElements];
   }
   // Wrapper around operator delete
   static void delete_AliXRDPROOFtoolkit(void *p) {
      delete ((::AliXRDPROOFtoolkit*)p);
   }
   static void deleteArray_AliXRDPROOFtoolkit(void *p) {
      delete [] ((::AliXRDPROOFtoolkit*)p);
   }
   static void destruct_AliXRDPROOFtoolkit(void *p) {
      typedef ::AliXRDPROOFtoolkit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliXRDPROOFtoolkit

//______________________________________________________________________________
void AliLog::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliLog.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliLog::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliLog::Class(),this);
   }
}

namespace ROOT {
} // end of namespace ROOT for class ::AliLog

//______________________________________________________________________________
void AliExternalTrackParam::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliExternalTrackParam.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliExternalTrackParam::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliExternalTrackParam::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AliExternalTrackParam(void *p) {
      return  p ? new(p) ::AliExternalTrackParam : new ::AliExternalTrackParam;
   }
   static void *newArray_AliExternalTrackParam(Long_t nElements, void *p) {
      return p ? new(p) ::AliExternalTrackParam[nElements] : new ::AliExternalTrackParam[nElements];
   }
   // Wrapper around operator delete
   static void delete_AliExternalTrackParam(void *p) {
      delete ((::AliExternalTrackParam*)p);
   }
   static void deleteArray_AliExternalTrackParam(void *p) {
      delete [] ((::AliExternalTrackParam*)p);
   }
   static void destruct_AliExternalTrackParam(void *p) {
      typedef ::AliExternalTrackParam current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliExternalTrackParam

namespace {
  void TriggerDictionaryInitialization_dict_AliExternalTrackParam_Impl() {
    static const char* headers[] = {
"AliVMisc.h",
"AliVParticle.h",
"AliVTrack.h",
"AliVVertex.h",
"TStatToolkit.h",
"AliTMinuitToolkit.h",
"AliPDG.h",
"AliPID.h",
"AliDrawStyle.h",
"AliSysInfo.h",
"AliXRDPROOFtoolkit.h",
"TTreeStream.h",
"AliLog.h",
"AliExternalTrackParam.h",
0
    };
    static const char* includePaths[] = {
"/opt/root/6.22.02-install/include/",
"/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/fastMCKalman/fastMCKalman/aliKalman/test/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "dict_AliExternalTrackParam dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate(R"ATTRDUMP(base class for particles)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$AliVParticle.h")))  AliVParticle;
class __attribute__((annotate(R"ATTRDUMP(particle id probability densities)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$AliPID.h")))  __attribute__((annotate("$clingAutoload$AliVTrack.h")))  AliPID;
class __attribute__((annotate(R"ATTRDUMP(base class for tracks)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$AliVTrack.h")))  AliVTrack;
class __attribute__((annotate(R"ATTRDUMP(base class for vertices)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$AliVVertex.h")))  AliVVertex;
class __attribute__((annotate("$clingAutoload$TTreeStream.h")))  __attribute__((annotate("$clingAutoload$TStatToolkit.h")))  TTreeDataElement;
class __attribute__((annotate("$clingAutoload$TTreeStream.h")))  __attribute__((annotate("$clingAutoload$TStatToolkit.h")))  TTreeStream;
class __attribute__((annotate("$clingAutoload$TTreeStream.h")))  __attribute__((annotate("$clingAutoload$TStatToolkit.h")))  TTreeSRedirector;
class __attribute__((annotate("$clingAutoload$AliTMinuitToolkit.h")))  AliTMinuitToolkit;
class __attribute__((annotate(R"ATTRDUMP(PDG database related information)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$AliPDG.h")))  AliPDG;
class __attribute__((annotate("$clingAutoload$AliDrawStyle.h")))  AliDrawStyle;
class __attribute__((annotate("$clingAutoload$AliSysInfo.h")))  AliSysInfo;
class __attribute__((annotate("$clingAutoload$AliXRDPROOFtoolkit.h")))  AliXRDPROOFtoolkit;
class __attribute__((annotate(R"ATTRDUMP(class for logging debug, info and error messages)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$AliLog.h")))  AliLog;
class __attribute__((annotate("$clingAutoload$AliExternalTrackParam.h")))  AliExternalTrackParam;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "dict_AliExternalTrackParam dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "AliVMisc.h"
#include "AliVParticle.h"
#include "AliVTrack.h"
#include "AliVVertex.h"
#include "TStatToolkit.h"
#include "AliTMinuitToolkit.h"
#include "AliPDG.h"
#include "AliPID.h"
#include "AliDrawStyle.h"
#include "AliSysInfo.h"
#include "AliXRDPROOFtoolkit.h"
#include "TTreeStream.h"
#include "AliLog.h"
#include "AliExternalTrackParam.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"AliDrawStyle", payloadCode, "@",
"AliExternalTrackParam", payloadCode, "@",
"AliLog", payloadCode, "@",
"AliPDG", payloadCode, "@",
"AliPID", payloadCode, "@",
"AliSysInfo", payloadCode, "@",
"AliTMinuitToolkit", payloadCode, "@",
"AliVParticle", payloadCode, "@",
"AliVTrack", payloadCode, "@",
"AliVVertex", payloadCode, "@",
"AliXRDPROOFtoolkit", payloadCode, "@",
"TTreeDataElement", payloadCode, "@",
"TTreeSRedirector", payloadCode, "@",
"TTreeStream", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("dict_AliExternalTrackParam",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_dict_AliExternalTrackParam_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_dict_AliExternalTrackParam_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_dict_AliExternalTrackParam() {
  TriggerDictionaryInitialization_dict_AliExternalTrackParam_Impl();
}
