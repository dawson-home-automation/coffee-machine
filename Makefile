clean:
		rm -rf .pioenvs

build-image:
		docker build -t platformio docker/build

compile:
		docker run -v $(shell pwd):/usr/src/app platformio platformio run

upload-%:
		curl -F "image=@remote_upload.ino.bin" http://$*/update

build: clean compile

build-all: build-image build
