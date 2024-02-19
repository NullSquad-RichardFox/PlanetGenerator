@echo off

ECHO A current build of Test Harness exists.
set /p buildVer=Select Visual Studio version: 

set useBuild = 0
IF %buildVer%==vs2022 set useBuild=vs2022
IF %buildVer%==vs2019 set useBuild=vs2019
IF %buildVer%==vs2017 set useBuild=vs2017
IF %buildVer%==vs2015 set useBuild=vs2015
IF %buildVer%==vs2013 set useBuild=vs2013
IF %buildVer%==vs2012 set useBuild=vs2012
IF %buildVer%==vs2010 set useBuild=vs2010
IF %buildVer%==vs2008 set useBuild=vs2008
IF %buildVer%==vs2005 set useBuild=vs2005

IF %buildVer%==2022 set useBuild=vs2022
IF %buildVer%==2019 set useBuild=vs2019
IF %buildVer%==2017 set useBuild=vs2017
IF %buildVer%==2015 set useBuild=vs2015
IF %buildVer%==2013 set useBuild=vs2013
IF %buildVer%==2012 set useBuild=vs2012
IF %buildVer%==2010 set useBuild=vs2010
IF %buildVer%==2008 set useBuild=vs2008
IF %buildVer%==2005 set useBuild=vs2005

IF %buildVer%==22 set useBuild=vs2022
IF %buildVer%==19 set useBuild=vs2019
IF %buildVer%==17 set useBuild=vs2017
IF %buildVer%==15 set useBuild=vs2015
IF %buildVer%==13 set useBuild=vs2013
IF %buildVer%==12 set useBuild=vs2012
IF %buildVer%==10 set useBuild=vs2010
IF %buildVer%==08 set useBuild=vs2008
IF %buildVer%==05 set useBuild=vs2005

IF %useBuild%==0 exit

pushd %~dp0\..\
call Programs\Premake\premake5.exe --file=PlanetGenerator.lua %useBuild%
popd
PAUSE