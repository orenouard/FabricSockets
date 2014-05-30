/*
 *  Copyright 2010-2014 Fabric Software Inc. All rights reserved.
 */

#ifndef __conversion_h__
#define __conversion_h__

#include "Handle.h"
#include <string>

using namespace Fabric::EDK;

template<class A, class B>
inline bool conv_from_baseType(const A & a, B & b)
{
  b = a;
  return true;
}

template<class B, class A>
inline bool conv_to_baseType(const A & a, B & b)
{
  b = a;
  return true;
}

inline bool conv_from_String(const KL::String & a, std::string & b)
{
  if(a.data() == NULL)
    b = "";
  else
    b = a.data();
  return true;
}

inline bool conv_to_String(const std::string & a, KL::String & b)
{
  if(a.length() == 0)
    b = "";
  else
    b = a.c_str();
  return true;
}

namespace IPVer
{
  inline NL::IPVer StringToEnum(const char* i_string)
  {
    if(!strcmp(i_string, "IP4") || !strcmp(i_string, "ip4"))
      return NL::IP4;
    else if(!strcmp(i_string, "IP6") || !strcmp(i_string, "ip6"))
      return NL::IP6;
    else if(!strcmp(i_string, "ANY") || !strcmp(i_string, "any"))
      return NL::ANY;           
    else
      FABRIC_EXT_SETERROR_AND_RETURN_VALUE(NL::ANY, "%s: %s", "Invalid IP version name", i_string);
  }  
  inline const char* EnumToString(const NL::IPVer i_enum)
  {
    switch(i_enum)
    {
      case NL::IP4:
        return "IP4";
      case NL::IP6:
        return "IP6";
      case NL::ANY:
        return "ANY";                    
      default:
        FABRIC_EXT_SETERROR_AND_RETURN_VALUE("", "%s: %i", "Invalid IP version code", int(i_enum));
    }
  }
}

namespace Protocol
{
  inline NL::Protocol StringToEnum(const char* i_string)
  {
    if(!strcmp(i_string, "TCP") || !strcmp(i_string, "tcp"))
      return NL::TCP;
    else if(!strcmp(i_string, "UDP") || !strcmp(i_string, "udp"))
      return NL::UDP;        
    else
      FABRIC_EXT_SETERROR_AND_RETURN_VALUE(NL::TCP, "%s: %s", "Invalid Protocol name", i_string);
  }  
  inline const char* EnumToString(const NL::Protocol i_enum)
  {
    switch(i_enum)
    {
      case NL::TCP:
        return "TCP";
      case NL::UDP:
        return "UDP";                
      default:
        FABRIC_EXT_SETERROR_AND_RETURN_VALUE("", "%s: %i", "Invalid Protocol code", int(i_enum));
    }
  }
}

namespace SocketType
{
  inline NL::SocketType StringToEnum(const char* i_string)
  {
    if(!strcmp(i_string, "CLIENT") || !strcmp(i_string, "client"))
      return NL::CLIENT;
    else if(!strcmp(i_string, "SERVER") || !strcmp(i_string, "server"))
      return NL::SERVER;        
    else
      FABRIC_EXT_SETERROR_AND_RETURN_VALUE(NL::CLIENT, "%s: %s", "Invalid Socket Type name", i_string);
  }  
  inline const char* EnumToString(const NL::SocketType i_enum)
  {
    switch(i_enum)
    {
      case NL::CLIENT:
        return "CLIENT";
      case NL::SERVER:
        return "SERVER";              
      default:
        FABRIC_EXT_SETERROR_AND_RETURN_VALUE("", "%s: %i", "Invalid Socket Type code", int(i_enum));
    }
  }
}

template<class A, class B>
inline bool conv_from_KLObject(const A & a, B * & b)
{
  if(!a.isValid())
    return false;
  Handle<B> * handle = (Handle<B> *)a->handle;
  if(handle == NULL)
    return false;
  b = handle->data();
  return true;
}

template<class B, class A>
inline bool conv_to_KLObject(const A * a, B & b, bool owned = false)
{
  if(!b.isValid())
    b = B::Create();
  if(b->handle != NULL)
    ((Handle<A> *)b->handle)->release();
  b->handle = new Handle<A>((A *)a, owned);
  return true;
}

#endif
