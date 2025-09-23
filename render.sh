PROJECTPATH=$1

if [ ! -f "$PROJECTPATH" ]; then
	echo "Project file does not exist"
	exit 1
fi

#Build project
echo "Compiling..."

cmake . -DPROJECT_PATH=$PROJECTPATH
make

echo "Running..."

./configrender