# libmongoc
## prerequisites
```
	sudo apt-get install cmake libssl-dev libsasl2-dev
```

## install
```
    //find suitable version. 1.13.0 or later is required. 
	wget https://github.com/mongodb/mongo-c-driver/releases/download/x.y.z/mongo-c-driver-x.y.z.tar.gz
	tar xzf mongo-c-driver-x.y.z.tar.gz
	cd mongo-c-driver-x.y.z
	mkdir cmake-build
	cd cmake-build
	cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..

    make && sudo make install

    //for uninstall
    //sudo /usr/local/share/mongo-c-driver/uninstall.sh
```


# mongocxx
```
    git clone https://github.com/mongodb/mongo-cxx-driver.git \
        --branch releases/stable --depth 1
    cd mongo-cxx-driver/build

    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..

    sudo make EP_mnmlstc_core

    make && sudo make install
```

# compile
use cmake `find_package()`