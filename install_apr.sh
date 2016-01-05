set -e

# go somewhere safe
cd /tmp

#get the source to base APR 1.4.6
curl -L -O http://archive.apache.org/dist/apr/apr-1.4.6.tar.gz

#extract it and go into src
tar -xzvf apr-1.4.6.tar.gz
cd apr-1.4.6

#config, make, install
./configure
make
sudo make install

#reset and clean up
cd /tmp
rm -rf apr-1.4.6 apr-1.4.6.tar.gz

curl -L -O http://archive.apache.org/dist/apr/apr-util-1.4.1.tar.gz

#extract
tar -xzvf apr-util-1.4.1.tar.gz
cd apr-util-1.4.1

#config, make, install
./configure --with-apr=/usr/local/apr
#need extra param because apr-util can't really find it on its own
make
sudo make install

#cleanup
cd /tmp
rm -rf apr-util-1.4.1* apr-1.4.6*
