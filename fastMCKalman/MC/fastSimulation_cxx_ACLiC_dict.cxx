// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIfedericodIDocumentsdIUniversitadIFederico_2020mI2021dIAliworkdIfastMCKalmanOptTestingdIfastMCKalmandIMCdIfastSimulation_cxx_ACLiC_dict
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
#include "/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/fastMCKalmanOptTesting/fastMCKalman/MC/fastSimulation.cxx"

// Header files passed via #pragma extra_include

   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *ROOT_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("ROOT", 0 /*version*/, "Rtypes.h", 103,
                     ::ROOT::Internal::DefineBehavior((void*)0,(void*)0),
                     &ROOT_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *ROOT_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }

namespace ROOT {
   static TClass *ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR_Dictionary();
   static void ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR_TClassManip(TClass*);
   static void *new_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR(void *p = 0);
   static void *newArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR(Long_t size, void *p);
   static void delete_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR(void *p);
   static void deleteArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR(void *p);
   static void destruct_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ROOT::VecOps::RVec<AliExternalTrackParam4D>*)
   {
      ::ROOT::VecOps::RVec<AliExternalTrackParam4D> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ROOT::VecOps::RVec<AliExternalTrackParam4D>));
      static ::ROOT::TGenericClassInfo 
         instance("ROOT::VecOps::RVec<AliExternalTrackParam4D>", "ROOT/RVec.hxx", 274,
                  typeid(::ROOT::VecOps::RVec<AliExternalTrackParam4D>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR_Dictionary, isa_proxy, 4,
                  sizeof(::ROOT::VecOps::RVec<AliExternalTrackParam4D>) );
      instance.SetNew(&new_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR);
      instance.SetNewArray(&newArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR);
      instance.SetDelete(&delete_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR);
      instance.SetDeleteArray(&deleteArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR);
      instance.SetDestructor(&destruct_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR);

      ::ROOT::AddClassAlternate("ROOT::VecOps::RVec<AliExternalTrackParam4D>","RVec<AliExternalTrackParam4D>");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ROOT::VecOps::RVec<AliExternalTrackParam4D>*)
   {
      return GenerateInitInstanceLocal((::ROOT::VecOps::RVec<AliExternalTrackParam4D>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ROOT::VecOps::RVec<AliExternalTrackParam4D>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::ROOT::VecOps::RVec<AliExternalTrackParam4D>*)0x0)->GetClass();
      ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR_TClassManip(theClass);
   return theClass;
   }

   static void ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR_Dictionary();
   static void ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR_TClassManip(TClass*);
   static void *new_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR(void *p = 0);
   static void *newArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR(Long_t size, void *p);
   static void delete_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR(void *p);
   static void deleteArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR(void *p);
   static void destruct_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ROOT::VecOps::RVec<AliExternalTrackParam>*)
   {
      ::ROOT::VecOps::RVec<AliExternalTrackParam> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ROOT::VecOps::RVec<AliExternalTrackParam>));
      static ::ROOT::TGenericClassInfo 
         instance("ROOT::VecOps::RVec<AliExternalTrackParam>", "ROOT/RVec.hxx", 274,
                  typeid(::ROOT::VecOps::RVec<AliExternalTrackParam>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR_Dictionary, isa_proxy, 4,
                  sizeof(::ROOT::VecOps::RVec<AliExternalTrackParam>) );
      instance.SetNew(&new_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR);
      instance.SetNewArray(&newArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR);
      instance.SetDelete(&delete_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR);
      instance.SetDeleteArray(&deleteArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR);
      instance.SetDestructor(&destruct_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR);

      ::ROOT::AddClassAlternate("ROOT::VecOps::RVec<AliExternalTrackParam>","RVec<AliExternalTrackParam>");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ROOT::VecOps::RVec<AliExternalTrackParam>*)
   {
      return GenerateInitInstanceLocal((::ROOT::VecOps::RVec<AliExternalTrackParam>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ROOT::VecOps::RVec<AliExternalTrackParam>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::ROOT::VecOps::RVec<AliExternalTrackParam>*)0x0)->GetClass();
      ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR_TClassManip(theClass);
   return theClass;
   }

   static void ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *ROOTcLcLVecOpscLcLRVeclEintgR_Dictionary();
   static void ROOTcLcLVecOpscLcLRVeclEintgR_TClassManip(TClass*);
   static void *new_ROOTcLcLVecOpscLcLRVeclEintgR(void *p = 0);
   static void *newArray_ROOTcLcLVecOpscLcLRVeclEintgR(Long_t size, void *p);
   static void delete_ROOTcLcLVecOpscLcLRVeclEintgR(void *p);
   static void deleteArray_ROOTcLcLVecOpscLcLRVeclEintgR(void *p);
   static void destruct_ROOTcLcLVecOpscLcLRVeclEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ROOT::VecOps::RVec<int>*)
   {
      ::ROOT::VecOps::RVec<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ROOT::VecOps::RVec<int>));
      static ::ROOT::TGenericClassInfo 
         instance("ROOT::VecOps::RVec<int>", "ROOT/RVec.hxx", 1756,
                  typeid(::ROOT::VecOps::RVec<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &ROOTcLcLVecOpscLcLRVeclEintgR_Dictionary, isa_proxy, 4,
                  sizeof(::ROOT::VecOps::RVec<int>) );
      instance.SetNew(&new_ROOTcLcLVecOpscLcLRVeclEintgR);
      instance.SetNewArray(&newArray_ROOTcLcLVecOpscLcLRVeclEintgR);
      instance.SetDelete(&delete_ROOTcLcLVecOpscLcLRVeclEintgR);
      instance.SetDeleteArray(&deleteArray_ROOTcLcLVecOpscLcLRVeclEintgR);
      instance.SetDestructor(&destruct_ROOTcLcLVecOpscLcLRVeclEintgR);

      ::ROOT::AddClassAlternate("ROOT::VecOps::RVec<int>","RVec<int>");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ROOT::VecOps::RVec<int>*)
   {
      return GenerateInitInstanceLocal((::ROOT::VecOps::RVec<int>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ROOT::VecOps::RVec<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ROOTcLcLVecOpscLcLRVeclEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::ROOT::VecOps::RVec<int>*)0x0)->GetClass();
      ROOTcLcLVecOpscLcLRVeclEintgR_TClassManip(theClass);
   return theClass;
   }

   static void ROOTcLcLVecOpscLcLRVeclEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *ROOTcLcLVecOpscLcLRVeclEfloatgR_Dictionary();
   static void ROOTcLcLVecOpscLcLRVeclEfloatgR_TClassManip(TClass*);
   static void *new_ROOTcLcLVecOpscLcLRVeclEfloatgR(void *p = 0);
   static void *newArray_ROOTcLcLVecOpscLcLRVeclEfloatgR(Long_t size, void *p);
   static void delete_ROOTcLcLVecOpscLcLRVeclEfloatgR(void *p);
   static void deleteArray_ROOTcLcLVecOpscLcLRVeclEfloatgR(void *p);
   static void destruct_ROOTcLcLVecOpscLcLRVeclEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ROOT::VecOps::RVec<float>*)
   {
      ::ROOT::VecOps::RVec<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ROOT::VecOps::RVec<float>));
      static ::ROOT::TGenericClassInfo 
         instance("ROOT::VecOps::RVec<float>", "ROOT/RVec.hxx", 1766,
                  typeid(::ROOT::VecOps::RVec<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &ROOTcLcLVecOpscLcLRVeclEfloatgR_Dictionary, isa_proxy, 4,
                  sizeof(::ROOT::VecOps::RVec<float>) );
      instance.SetNew(&new_ROOTcLcLVecOpscLcLRVeclEfloatgR);
      instance.SetNewArray(&newArray_ROOTcLcLVecOpscLcLRVeclEfloatgR);
      instance.SetDelete(&delete_ROOTcLcLVecOpscLcLRVeclEfloatgR);
      instance.SetDeleteArray(&deleteArray_ROOTcLcLVecOpscLcLRVeclEfloatgR);
      instance.SetDestructor(&destruct_ROOTcLcLVecOpscLcLRVeclEfloatgR);

      ::ROOT::AddClassAlternate("ROOT::VecOps::RVec<float>","RVec<float>");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ROOT::VecOps::RVec<float>*)
   {
      return GenerateInitInstanceLocal((::ROOT::VecOps::RVec<float>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ROOT::VecOps::RVec<float>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ROOTcLcLVecOpscLcLRVeclEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::ROOT::VecOps::RVec<float>*)0x0)->GetClass();
      ROOTcLcLVecOpscLcLRVeclEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void ROOTcLcLVecOpscLcLRVeclEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_AliExternalTrackParam4D(void *p = 0);
   static void *newArray_AliExternalTrackParam4D(Long_t size, void *p);
   static void delete_AliExternalTrackParam4D(void *p);
   static void deleteArray_AliExternalTrackParam4D(void *p);
   static void destruct_AliExternalTrackParam4D(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::AliExternalTrackParam4D*)
   {
      ::AliExternalTrackParam4D *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::AliExternalTrackParam4D >(0);
      static ::ROOT::TGenericClassInfo 
         instance("AliExternalTrackParam4D", ::AliExternalTrackParam4D::Class_Version(), "fastSimulation.h", 26,
                  typeid(::AliExternalTrackParam4D), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::AliExternalTrackParam4D::Dictionary, isa_proxy, 4,
                  sizeof(::AliExternalTrackParam4D) );
      instance.SetNew(&new_AliExternalTrackParam4D);
      instance.SetNewArray(&newArray_AliExternalTrackParam4D);
      instance.SetDelete(&delete_AliExternalTrackParam4D);
      instance.SetDeleteArray(&deleteArray_AliExternalTrackParam4D);
      instance.SetDestructor(&destruct_AliExternalTrackParam4D);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::AliExternalTrackParam4D*)
   {
      return GenerateInitInstanceLocal((::AliExternalTrackParam4D*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::AliExternalTrackParam4D*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_fastGeometry(void *p = 0);
   static void *newArray_fastGeometry(Long_t size, void *p);
   static void delete_fastGeometry(void *p);
   static void deleteArray_fastGeometry(void *p);
   static void destruct_fastGeometry(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::fastGeometry*)
   {
      ::fastGeometry *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::fastGeometry >(0);
      static ::ROOT::TGenericClassInfo 
         instance("fastGeometry", ::fastGeometry::Class_Version(), "fastSimulation.h", 65,
                  typeid(::fastGeometry), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::fastGeometry::Dictionary, isa_proxy, 4,
                  sizeof(::fastGeometry) );
      instance.SetNew(&new_fastGeometry);
      instance.SetNewArray(&newArray_fastGeometry);
      instance.SetDelete(&delete_fastGeometry);
      instance.SetDeleteArray(&deleteArray_fastGeometry);
      instance.SetDestructor(&destruct_fastGeometry);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::fastGeometry*)
   {
      return GenerateInitInstanceLocal((::fastGeometry*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::fastGeometry*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_fastParticle(void *p = 0);
   static void *newArray_fastParticle(Long_t size, void *p);
   static void delete_fastParticle(void *p);
   static void deleteArray_fastParticle(void *p);
   static void destruct_fastParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::fastParticle*)
   {
      ::fastParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::fastParticle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("fastParticle", ::fastParticle::Class_Version(), "fastSimulation.h", 86,
                  typeid(::fastParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::fastParticle::Dictionary, isa_proxy, 4,
                  sizeof(::fastParticle) );
      instance.SetNew(&new_fastParticle);
      instance.SetNewArray(&newArray_fastParticle);
      instance.SetDelete(&delete_fastParticle);
      instance.SetDeleteArray(&deleteArray_fastParticle);
      instance.SetDestructor(&destruct_fastParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::fastParticle*)
   {
      return GenerateInitInstanceLocal((::fastParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::fastParticle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr AliExternalTrackParam4D::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *AliExternalTrackParam4D::Class_Name()
{
   return "AliExternalTrackParam4D";
}

//______________________________________________________________________________
const char *AliExternalTrackParam4D::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliExternalTrackParam4D*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int AliExternalTrackParam4D::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::AliExternalTrackParam4D*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *AliExternalTrackParam4D::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliExternalTrackParam4D*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *AliExternalTrackParam4D::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::AliExternalTrackParam4D*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr fastGeometry::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *fastGeometry::Class_Name()
{
   return "fastGeometry";
}

//______________________________________________________________________________
const char *fastGeometry::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::fastGeometry*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int fastGeometry::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::fastGeometry*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *fastGeometry::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::fastGeometry*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *fastGeometry::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::fastGeometry*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr fastParticle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *fastParticle::Class_Name()
{
   return "fastParticle";
}

//______________________________________________________________________________
const char *fastParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::fastParticle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int fastParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::fastParticle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *fastParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::fastParticle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *fastParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::fastParticle*)0x0)->GetClass(); }
   return fgIsA;
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::ROOT::VecOps::RVec<AliExternalTrackParam4D> : new ::ROOT::VecOps::RVec<AliExternalTrackParam4D>;
   }
   static void *newArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::ROOT::VecOps::RVec<AliExternalTrackParam4D>[nElements] : new ::ROOT::VecOps::RVec<AliExternalTrackParam4D>[nElements];
   }
   // Wrapper around operator delete
   static void delete_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR(void *p) {
      delete ((::ROOT::VecOps::RVec<AliExternalTrackParam4D>*)p);
   }
   static void deleteArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR(void *p) {
      delete [] ((::ROOT::VecOps::RVec<AliExternalTrackParam4D>*)p);
   }
   static void destruct_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParam4DgR(void *p) {
      typedef ::ROOT::VecOps::RVec<AliExternalTrackParam4D> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ROOT::VecOps::RVec<AliExternalTrackParam4D>

namespace ROOT {
   // Wrappers around operator new
   static void *new_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::ROOT::VecOps::RVec<AliExternalTrackParam> : new ::ROOT::VecOps::RVec<AliExternalTrackParam>;
   }
   static void *newArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::ROOT::VecOps::RVec<AliExternalTrackParam>[nElements] : new ::ROOT::VecOps::RVec<AliExternalTrackParam>[nElements];
   }
   // Wrapper around operator delete
   static void delete_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR(void *p) {
      delete ((::ROOT::VecOps::RVec<AliExternalTrackParam>*)p);
   }
   static void deleteArray_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR(void *p) {
      delete [] ((::ROOT::VecOps::RVec<AliExternalTrackParam>*)p);
   }
   static void destruct_ROOTcLcLVecOpscLcLRVeclEAliExternalTrackParamgR(void *p) {
      typedef ::ROOT::VecOps::RVec<AliExternalTrackParam> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ROOT::VecOps::RVec<AliExternalTrackParam>

namespace ROOT {
   // Wrappers around operator new
   static void *new_ROOTcLcLVecOpscLcLRVeclEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::ROOT::VecOps::RVec<int> : new ::ROOT::VecOps::RVec<int>;
   }
   static void *newArray_ROOTcLcLVecOpscLcLRVeclEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::ROOT::VecOps::RVec<int>[nElements] : new ::ROOT::VecOps::RVec<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_ROOTcLcLVecOpscLcLRVeclEintgR(void *p) {
      delete ((::ROOT::VecOps::RVec<int>*)p);
   }
   static void deleteArray_ROOTcLcLVecOpscLcLRVeclEintgR(void *p) {
      delete [] ((::ROOT::VecOps::RVec<int>*)p);
   }
   static void destruct_ROOTcLcLVecOpscLcLRVeclEintgR(void *p) {
      typedef ::ROOT::VecOps::RVec<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ROOT::VecOps::RVec<int>

namespace ROOT {
   // Wrappers around operator new
   static void *new_ROOTcLcLVecOpscLcLRVeclEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::ROOT::VecOps::RVec<float> : new ::ROOT::VecOps::RVec<float>;
   }
   static void *newArray_ROOTcLcLVecOpscLcLRVeclEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::ROOT::VecOps::RVec<float>[nElements] : new ::ROOT::VecOps::RVec<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_ROOTcLcLVecOpscLcLRVeclEfloatgR(void *p) {
      delete ((::ROOT::VecOps::RVec<float>*)p);
   }
   static void deleteArray_ROOTcLcLVecOpscLcLRVeclEfloatgR(void *p) {
      delete [] ((::ROOT::VecOps::RVec<float>*)p);
   }
   static void destruct_ROOTcLcLVecOpscLcLRVeclEfloatgR(void *p) {
      typedef ::ROOT::VecOps::RVec<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ROOT::VecOps::RVec<float>

//______________________________________________________________________________
void AliExternalTrackParam4D::Streamer(TBuffer &R__b)
{
   // Stream an object of class AliExternalTrackParam4D.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(AliExternalTrackParam4D::Class(),this);
   } else {
      R__b.WriteClassBuffer(AliExternalTrackParam4D::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_AliExternalTrackParam4D(void *p) {
      return  p ? new(p) ::AliExternalTrackParam4D : new ::AliExternalTrackParam4D;
   }
   static void *newArray_AliExternalTrackParam4D(Long_t nElements, void *p) {
      return p ? new(p) ::AliExternalTrackParam4D[nElements] : new ::AliExternalTrackParam4D[nElements];
   }
   // Wrapper around operator delete
   static void delete_AliExternalTrackParam4D(void *p) {
      delete ((::AliExternalTrackParam4D*)p);
   }
   static void deleteArray_AliExternalTrackParam4D(void *p) {
      delete [] ((::AliExternalTrackParam4D*)p);
   }
   static void destruct_AliExternalTrackParam4D(void *p) {
      typedef ::AliExternalTrackParam4D current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::AliExternalTrackParam4D

//______________________________________________________________________________
void fastGeometry::Streamer(TBuffer &R__b)
{
   // Stream an object of class fastGeometry.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(fastGeometry::Class(),this);
   } else {
      R__b.WriteClassBuffer(fastGeometry::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_fastGeometry(void *p) {
      return  p ? new(p) ::fastGeometry : new ::fastGeometry;
   }
   static void *newArray_fastGeometry(Long_t nElements, void *p) {
      return p ? new(p) ::fastGeometry[nElements] : new ::fastGeometry[nElements];
   }
   // Wrapper around operator delete
   static void delete_fastGeometry(void *p) {
      delete ((::fastGeometry*)p);
   }
   static void deleteArray_fastGeometry(void *p) {
      delete [] ((::fastGeometry*)p);
   }
   static void destruct_fastGeometry(void *p) {
      typedef ::fastGeometry current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::fastGeometry

//______________________________________________________________________________
void fastParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class fastParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(fastParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(fastParticle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_fastParticle(void *p) {
      return  p ? new(p) ::fastParticle : new ::fastParticle;
   }
   static void *newArray_fastParticle(Long_t nElements, void *p) {
      return p ? new(p) ::fastParticle[nElements] : new ::fastParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_fastParticle(void *p) {
      delete ((::fastParticle*)p);
   }
   static void deleteArray_fastParticle(void *p) {
      delete [] ((::fastParticle*)p);
   }
   static void destruct_fastParticle(void *p) {
      typedef ::fastParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::fastParticle

namespace ROOT {
   static TClass *vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR_Dictionary();
   static void vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR(void *p = 0);
   static void *newArray_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR(Long_t size, void *p);
   static void delete_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR(void *p);
   static void deleteArray_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR(void *p);
   static void destruct_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >*)
   {
      vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >", -2, "vector", 386,
                  typeid(vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >) );
      instance.SetNew(&new_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR);
      instance.SetNewArray(&newArray_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR);
      instance.SetDelete(&delete_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR);
      instance.SetDestructor(&destruct_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> > >()));

      ::ROOT::AddClassAlternate("vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >","std::vector<int, ROOT::Detail::VecOps::RAdoptAllocator<int> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >*)0x0)->GetClass();
      vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> > : new vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >;
   }
   static void *newArray_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >[nElements] : new vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR(void *p) {
      delete ((vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >*)p);
   }
   static void deleteArray_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR(void *p) {
      delete [] ((vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >*)p);
   }
   static void destruct_vectorlEintcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEintgRsPgR(void *p) {
      typedef vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int,ROOT::Detail::VecOps::RAdoptAllocator<int> >

namespace ROOT {
   static TClass *vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR_Dictionary();
   static void vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR(void *p = 0);
   static void *newArray_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR(Long_t size, void *p);
   static void delete_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR(void *p);
   static void deleteArray_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR(void *p);
   static void destruct_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >*)
   {
      vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >", -2, "vector", 386,
                  typeid(vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >) );
      instance.SetNew(&new_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR);
      instance.SetNewArray(&newArray_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR);
      instance.SetDelete(&delete_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR);
      instance.SetDestructor(&destruct_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > >()));

      ::ROOT::AddClassAlternate("vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >","std::vector<float, ROOT::Detail::VecOps::RAdoptAllocator<float> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >*)0x0)->GetClass();
      vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > : new vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >;
   }
   static void *newArray_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >[nElements] : new vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR(void *p) {
      delete ((vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >*)p);
   }
   static void deleteArray_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR(void *p) {
      delete [] ((vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >*)p);
   }
   static void destruct_vectorlEfloatcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEfloatgRsPgR(void *p) {
      typedef vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float,ROOT::Detail::VecOps::RAdoptAllocator<float> >

namespace ROOT {
   static TClass *vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR_Dictionary();
   static void vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR(void *p = 0);
   static void *newArray_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR(Long_t size, void *p);
   static void delete_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR(void *p);
   static void deleteArray_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR(void *p);
   static void destruct_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >*)
   {
      vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >", -2, "vector", 386,
                  typeid(vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >) );
      instance.SetNew(&new_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR);
      instance.SetNewArray(&newArray_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR);
      instance.SetDelete(&delete_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR);
      instance.SetDestructor(&destruct_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> > >()));

      ::ROOT::AddClassAlternate("vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >","std::vector<AliExternalTrackParam4D, ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >*)0x0)->GetClass();
      vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> > : new vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >;
   }
   static void *newArray_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >[nElements] : new vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR(void *p) {
      delete ((vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >*)p);
   }
   static void deleteArray_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR(void *p) {
      delete [] ((vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >*)p);
   }
   static void destruct_vectorlEAliExternalTrackParam4DcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParam4DgRsPgR(void *p) {
      typedef vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<AliExternalTrackParam4D,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam4D> >

namespace ROOT {
   static TClass *vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR_Dictionary();
   static void vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR(void *p = 0);
   static void *newArray_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR(Long_t size, void *p);
   static void delete_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR(void *p);
   static void deleteArray_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR(void *p);
   static void destruct_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >*)
   {
      vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >", -2, "vector", 386,
                  typeid(vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >) );
      instance.SetNew(&new_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR);
      instance.SetNewArray(&newArray_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR);
      instance.SetDelete(&delete_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR);
      instance.SetDestructor(&destruct_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> > >()));

      ::ROOT::AddClassAlternate("vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >","std::vector<AliExternalTrackParam, ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >*)0x0)->GetClass();
      vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> > : new vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >;
   }
   static void *newArray_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >[nElements] : new vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR(void *p) {
      delete ((vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >*)p);
   }
   static void deleteArray_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR(void *p) {
      delete [] ((vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >*)p);
   }
   static void destruct_vectorlEAliExternalTrackParamcOROOTcLcLDetailcLcLVecOpscLcLRAdoptAllocatorlEAliExternalTrackParamgRsPgR(void *p) {
      typedef vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<AliExternalTrackParam,ROOT::Detail::VecOps::RAdoptAllocator<AliExternalTrackParam> >

namespace {
  void TriggerDictionaryInitialization_fastSimulation_cxx_ACLiC_dict_Impl() {
    static const char* headers[] = {
"fastSimulation.cxx",
0
    };
    static const char* includePaths[] = {
"/opt/root/6.22.02-install/include",
"/opt/root/6.22.02-install/etc/",
"/opt/root/6.22.02-install/etc//cling",
"/opt/root/6.22.02-install/include/",
"/usr/include/python3.8",
"/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/fastMCKalmanOptTesting/fastMCKalman/aliKalman/test/",
"/opt/root/6.22.02-install/include/",
"/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/fastMCKalmanOptTesting/fastMCKalman/MC/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "fastSimulation_cxx_ACLiC_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/fastMCKalmanOptTesting/fastMCKalman/MC/fastSimulation.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$fastSimulation.h")))  __attribute__((annotate("$clingAutoload$fastSimulation.cxx")))  AliExternalTrackParam4D;
namespace ROOT{namespace VecOps{template <typename T> class __attribute__((annotate("$clingAutoload$ROOT/RVec.hxx")))  __attribute__((annotate("$clingAutoload$fastSimulation.cxx")))  RVec;
}}
class __attribute__((annotate("$clingAutoload$AliExternalTrackParam.h")))  __attribute__((annotate("$clingAutoload$fastSimulation.cxx")))  AliExternalTrackParam;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/fastMCKalmanOptTesting/fastMCKalman/MC/fastSimulation.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$fastSimulation.h")))  __attribute__((annotate("$clingAutoload$fastSimulation.cxx")))  fastGeometry;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@/home/federico/Documents/Universita/Federico_2020-2021/Aliwork/fastMCKalmanOptTesting/fastMCKalman/MC/fastSimulation.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$fastSimulation.h")))  __attribute__((annotate("$clingAutoload$fastSimulation.cxx")))  fastParticle;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "fastSimulation_cxx_ACLiC_dict dictionary payload"

#ifndef __ACLIC__
  #define __ACLIC__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "fastSimulation.cxx"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"AliExternalTrackParam4D", payloadCode, "@",
"AliExternalTrackParam4D::fgIsA", payloadCode, "@",
"ROOT::GenerateInitInstance", payloadCode, "@",
"ROOT::VecOps::RVec<AliExternalTrackParam4D>", payloadCode, "@",
"ROOT::VecOps::RVec<AliExternalTrackParam>", payloadCode, "@",
"ROOT::VecOps::RVec<float>", payloadCode, "@",
"ROOT::VecOps::RVec<int>", payloadCode, "@",
"RVec<AliExternalTrackParam4D>", payloadCode, "@",
"RVec<AliExternalTrackParam>", payloadCode, "@",
"RVec<float>", payloadCode, "@",
"RVec<int>", payloadCode, "@",
"fastGeometry", payloadCode, "@",
"fastGeometry::fgIsA", payloadCode, "@",
"fastParticle", payloadCode, "@",
"fastParticle::TrackingBits", payloadCode, "@",
"fastParticle::fgIsA", payloadCode, "@",
"fastParticle::fgStreamer", payloadCode, "@",
"fracUnitTest", payloadCode, "@",
"getHelix", payloadCode, "@",
"kMaxLayers", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("fastSimulation_cxx_ACLiC_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_fastSimulation_cxx_ACLiC_dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_fastSimulation_cxx_ACLiC_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_fastSimulation_cxx_ACLiC_dict() {
  TriggerDictionaryInitialization_fastSimulation_cxx_ACLiC_dict_Impl();
}
