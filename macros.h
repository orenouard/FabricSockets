/*
 *  Copyright 2010-2014 Fabric Software Inc. All rights reserved.
 */

#ifndef __macros_h__
#define __macros_h__

#define QUOTEDNAME(name) #name
#define SOCKETS_TRY_STATEMENT(functionName) try {
#define SOCKETS_CATCH_STATEMENT(functionName) } catch (std::runtime_error e) { \
  FABRIC_EXT_SETERROR_AND_RETURN("%s: %s", QUOTEDNAME(functionName), e.what()); \
} catch (NL::Exception e) { \
  FABRIC_EXT_SETERROR_AND_RETURN("%s: %s", QUOTEDNAME(functionName), e.what()); \
}
#define SOCKETS_CATCH_STATEMENT_RETURN(functionName, value) } catch (std::runtime_error e) { \
  FABRIC_EXT_SETERROR_AND_RETURN_VALUE(value, "%s: %s", QUOTEDNAME(functionName), e.what()); \
} catch (NL::Exception e) { \
  FABRIC_EXT_SETERROR_AND_RETURN_VALUE(value, "%s: %s", QUOTEDNAME(functionName), e.what()); \
}

#endif