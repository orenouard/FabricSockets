#
# Fabric Core 1.11.4
# SCons build 'header' for Fabric Core EDK
#
# Copyright 2010-2014 Fabric Software Inc. All rights reserved.
#

import os, platform, sys

buildOS = os.environ.get('FABRIC_BUILD_OS', platform.system())
supportedOSes = ['Windows', 'Linux', 'Darwin']
try:
  if not buildOS in supportedOSes:
    raise Exception("Unrecognized OS '" + buildOS + "'")
except Exception as e:
  print e
  print "You can set FABRIC_BUILD_OS in your environment to override."
  print "Can be one of: " + ', '.join(supportedOSes)
  sys.exit(1)

buildArch = os.environ.get('FABRIC_BUILD_ARCH', platform.architecture()[0])
pythonArchToFabricArch = {
  "Darwin": {
    "x86_64": "x86_64",
    "64bit": "x86_64",
    "universal": "x86_64",
  },
  "Linux": {
    "i686": "i686",
    "i386": "i686",
    "32bit": "i686",
    "amd64": "x86_64",
    "x86_64": "x86_64",
    "64bit": "x86_64",
  },
  "Windows": {
    "x86": "x86",
    "32bit": "x86",
    "x86_64": "x86_64",
    "x64": "x86_64",
    "64bit": "x86_64",
  },
}
try:
  buildArch = pythonArchToFabricArch[buildOS][buildArch]
except:
  print "Unrecognized architecture '" + buildArch + "' for OS '" + buildOS + "'"
  print "You can set FABRIC_BUILD_ARCH in your environment to override."
  print "Can be one of: " + ', '.join(keys(pythonArchToFabricArch[buildOS]))
  sys.exit(1)

buildType = os.environ.get('FABRIC_BUILD_TYPE', 'Release')

fabricBuildEnv = Environment(
  ENV = { 'PATH': os.environ['PATH'] },
  FABRIC_CORE_VERSION_MAJ = '1',
  FABRIC_CORE_VERSION_MIN = '11',
  FABRIC_CORE_VERSION_REV = '4',
  FABRIC_CORE_VERSION_NO_SUFFIX = '1.11.4',
  FABRIC_CORE_VERSION = '1.11.4',
  FABRIC_CORE_VERSION_SUFFIX = '',
  FABRIC_CORE_MODULE_NAME = 'Fabric Core',
  FABRIC_DESC = 'Dedicated Platform for High-Performance Graphics Applications',
  FABRIC_BUILD_OS = buildOS,
  FABRIC_BUILD_ARCH = buildArch,
  FABRIC_BUILD_TYPE = buildType,
  # TARGET_ARCH must be set when the Environment() is created in order
  # to pull in correct x86 vs x64 paths on Windows
  TARGET_ARCH = buildArch
  )

if buildOS == 'Windows':
  fabricBuildEnv.Append(ENV = {"APPDATA": os.environ['APPDATA']})
else:
  fabricBuildEnv.Append(ENV = {"HOME": os.environ['HOME']})

SetOption('num_jobs', int(os.environ.get('FABRIC_BUILD_JOBS', 1)))
print "Running SCons with -j" + str(GetOption('num_jobs'))

if not ARGUMENTS.get('VERBOSE'):
  fabricBuildEnv['CCCOMSTR']       = 'Compiling       $SOURCE'
  fabricBuildEnv['CXXCOMSTR']      = 'Compiling       $SOURCE'
  fabricBuildEnv['SHCCCOMSTR']     = 'Compiling       $SOURCE'
  fabricBuildEnv['SHCXXCOMSTR']    = 'Compiling       $SOURCE'
  fabricBuildEnv['ARCOMSTR']       = 'StaticLibrary   $TARGET'
  fabricBuildEnv['SHLINKCOMSTR']   = 'SharedLibrary   $TARGET'
  fabricBuildEnv['RANLIBCOMSTR']   = 'Ranlib          $TARGET'
  fabricBuildEnv['LINKCOMSTR']     = 'Linking         $TARGET'
  fabricBuildEnv['LDMODULECOMSTR'] = 'LoadableModule  $TARGET'

if buildType == 'Release':
  fabricBuildEnv.Append(CPPDEFINES = ['NDEBUG'])

if buildOS == 'Windows' and buildType == 'Debug':
  fabricBuildEnv.Append(PDB  = '${TARGET.base}.pdb')

if buildOS == 'Windows':
  fabricBuildEnv['ENV']['TMP'] = os.environ.get('TMP', os.environ.get('TEMP', "C:\\TEMP"))

try:
  fabricEDKDir = fabricBuildEnv.Dir(os.environ['FABRIC_EDK_DIR'])
except:
  print "You must set FABRIC_EDK_DIR in your environment."
  print "Normally, this is set as part of the installation of"
  print "Fabric Core; perhaps try reinstallation?"
  sys.exit(1)
fabricBuildEnv.Append(CPPPATH = [
  fabricEDKDir.Dir('include'),
  ])

try:
  fabricToolsDir = fabricBuildEnv.Dir(os.environ['FABRIC_TOOLS_DIR'])
except:
  print "You must set FABRIC_TOOLS_DIR in your environment."
  print "Normally, this is set as part of the installation of"
  print "Fabric Core; perhaps try reinstallation?"
  sys.exit(1)

# check for buildOS specific flags
buildFlags = { 
  # === OSX ===
  'Darwin': {
    'ccflags': ['-Wall', '-fvisibility=hidden', '-mmacosx-version-min=10.7'],
    'linkflags': ['-w', '-mmacosx-version-min=10.7'],
    'x86_64' : {
      'ccflags': ['-arch', 'x86_64'],
      'linkflags': ['-arch', 'x86_64']
      },
    'Debug' : {
      'ccflags': [ '-g' ]
      },
    'Release' : {
      'ccflags': [ '-O2' ]
      },
    }, 
  # === LINUX ===
  'Linux': {
    'ccDefs': [
      '__STDC_LIMIT_MACROS',
      '__STDC_CONSTANT_MACROS'
    ],
    'ccflags': ['-fPIC'],
    'i686' : {
      'ccflags': [ '-m32' ],
      'linkflags': [ '-m32' ]
      },
    'x86_64' : {
      'ccflags': [ '-m64' ],
      'linkflags': [ '-m64' ]
      },
    'Debug' : {
      'ccflags': [ '-g' ]
      },
    'Release' : {
      'ccflags': [ '-O2' ]
      },
    }, 
  # === WINDOWS ===
  'Windows': {
    'ccDefs': [ 
      '_SCL_SECURE_NO_WARNINGS=1',
      '_ITERATOR_DEBUG_LEVEL=0',
      '_SECURE_SCL=0',
      '_WIN32_WINNT=0x0600'
    ],
    'ccflags': [ 
      '/EHsc', 
      '/wd4624'    ],
    'linkflags': [ 'chkstk.obj' ],
    'x86' : {
      'ccflags': [ ],
      'linkflags': [ ]
      },
    'x86_64' : {
      'ccDefs': [ 'WIN64' ],
      'ccflags': [ ],
      'linkflags': [ ]
      },
    'Debug' : {
      'ccflags': [ '/Od', '/Z7', '/MTd' ]
      },
    'Release' : {
      'ccflags': [ '/Ox', '/MT' ]
      },
    }
  }

osFlags = buildFlags[buildOS]

if 'ccDefs' in osFlags:
  fabricBuildEnv.Append( CPPDEFINES = osFlags['ccDefs'] )  
if 'ccflags' in osFlags:
  fabricBuildEnv.Append( CCFLAGS = osFlags['ccflags'] )
if 'cxxflags' in osFlags:
  fabricBuildEnv.Append( CXXFLAGS = osFlags['cxxflags'] )
if 'linkflags' in osFlags:
  fabricBuildEnv.Append( LINKFLAGS = osFlags['linkflags'] )

subTypes = [ buildArch, buildType ]
for subType in subTypes:
  if subType in osFlags:
    osSubFlags = osFlags[subType]
    if 'ccDefs' in osSubFlags:
      fabricBuildEnv.Append( CPPDEFINES = osSubFlags['ccDefs'] )  
    if 'ccflags' in osSubFlags:
      fabricBuildEnv.Append( CCFLAGS = osSubFlags['ccflags'] )
    if 'cxxflags' in osSubFlags:
      fabricBuildEnv.Append( CXXFLAGS = osSubFlags['cxxflags'] )
    if 'linkflags' in osSubFlags:
      fabricBuildEnv.Append( LINKFLAGS = osSubFlags['linkflags'] )

def buildExtension(env, target, sources):
  env.Append(CPPPATH = [env.Dir('.')])
  
  # fabricBuildEnv buildExtension doesn't take json files as sources for kl2edk
  
  cppHeaders = []
  cppSources = []
  klSources = []
  jsonfpm = []
  jsoncodegen = []
  for source in Flatten(sources):
    if str(source)[-2:] == '.h':
      cppHeaders.append(File(source))    
    elif str(source)[-3:] == '.kl':
      klSources.append(File(source))
    elif str(source)[-4:] == '.cpp':
      cppSources.append(File(source))
    elif str(source)[-8:] == 'fpm.json':
      jsonfpm.append(File(source))
    elif str(source)[-12:] == 'codegen.json':
      jsoncodegen.append(File(source))   
  
  kl2edkSources = jsonfpm + jsoncodegen + klSources
  
  if buildOS == 'Windows':
    kl2edkBin = fabricToolsDir.File('kl2edk.exe')
  else:
    if 'LD_LIBRARY_PATH' in os.environ:
      env['ENV']['LD_LIBRARY_PATH'] = os.environ['LD_LIBRARY_PATH']
    kl2edkBin = fabricToolsDir.File('kl2edk')
   
  kl2edkResults = []
  kl2edkTargets = []
  for source in klSources :
    name = str(source)[:-3]
    if name == target :
      kl2edkTargets.append(File("global.h"))
      kl2edkTargets.append(File("global_functions.h"))
      if jsoncodegen :
        kl2edkTargets.append(File("extension.cpp"))
        kl2edkTargets.append(File("global_functions.cpp"))       
    else :
      kl2edkTargets.append(File(name+".h"))
      kl2edkTargets.append(File(name+"_functions.h"))
      if jsoncodegen :
        kl2edkTargets.append(File(name+"_functions.cpp"))
  if jsoncodegen :
    kl2edkResults += env.Command(
      kl2edkTargets,
      kl2edkSources,
      [[kl2edkBin, "-o", "${TARGET.dir}", "-c", "${TARGET.dir}", "--overwrite-cpp-files"] + kl2edkSources]
      )
  else :
    kl2edkResults += env.Command(
      kl2edkTargets,
      kl2edkSources,
      [[kl2edkBin, "-o", "${TARGET.dir}"] + kl2edkSources]
      )

  for source in Flatten(kl2edkTargets):
    if str(source)[-2:] == '.h' and not source in cppHeaders:
	  cppHeaders.append(File(source))
    if str(source)[-4:] == '.cpp' and not source in cppSources:
	  cppSources.append(File(source))
  	
  env.Depends(cppHeaders, kl2edkSources)
  if jsoncodegen :
    env.Depends(cppSources, kl2edkSources)
  else :
    env.Depends(cppSources, cppHeaders)

  libraryFiles = Flatten([env.SharedLibrary('-'.join([target, buildOS, buildArch]), cppSources)])
  env.Depends(libraryFiles, cppSources)
  
  return libraryFiles
fabricBuildEnv.AddMethod(buildExtension, 'Extension')

Export('fabricBuildEnv')
