MATLAB="/usr/local/MATLAB/R2011b"
Arch=glnxa64
ENTRYPOINT=mexFunction
MAPFILE=$ENTRYPOINT'.map'
PREFDIR="/home/ying/.matlab/R2011b"
OPTSFILE_NAME="./mexopts.sh"
. $OPTSFILE_NAME
COMPILER=$CC
. $OPTSFILE_NAME
echo "# Make settings for sphere_on_sphere" > sphere_on_sphere_mex.mki
echo "CC=$CC" >> sphere_on_sphere_mex.mki
echo "CFLAGS=$CFLAGS" >> sphere_on_sphere_mex.mki
echo "CLIBS=$CLIBS" >> sphere_on_sphere_mex.mki
echo "COPTIMFLAGS=$COPTIMFLAGS" >> sphere_on_sphere_mex.mki
echo "CDEBUGFLAGS=$CDEBUGFLAGS" >> sphere_on_sphere_mex.mki
echo "CXX=$CXX" >> sphere_on_sphere_mex.mki
echo "CXXFLAGS=$CXXFLAGS" >> sphere_on_sphere_mex.mki
echo "CXXLIBS=$CXXLIBS" >> sphere_on_sphere_mex.mki
echo "CXXOPTIMFLAGS=$CXXOPTIMFLAGS" >> sphere_on_sphere_mex.mki
echo "CXXDEBUGFLAGS=$CXXDEBUGFLAGS" >> sphere_on_sphere_mex.mki
echo "LD=$LD" >> sphere_on_sphere_mex.mki
echo "LDFLAGS=$LDFLAGS" >> sphere_on_sphere_mex.mki
echo "LDOPTIMFLAGS=$LDOPTIMFLAGS" >> sphere_on_sphere_mex.mki
echo "LDDEBUGFLAGS=$LDDEBUGFLAGS" >> sphere_on_sphere_mex.mki
echo "Arch=$Arch" >> sphere_on_sphere_mex.mki
echo OMPFLAGS= >> sphere_on_sphere_mex.mki
echo OMPLINKFLAGS= >> sphere_on_sphere_mex.mki
echo "EMC_COMPILER=unix" >> sphere_on_sphere_mex.mki
echo "EMC_CONFIG=optim" >> sphere_on_sphere_mex.mki
"/usr/local/MATLAB/R2011b/bin/glnxa64/gmake" -B -f sphere_on_sphere_mex.mk
