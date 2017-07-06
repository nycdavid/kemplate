image:
	docker build \
	-t cppgd \
	.
compile:
	docker run \
	-v $(shell pwd):/app \
	--rm \
	cppgd:latest \
	/bin/ash -c "g++ -std=c++11 -o /app/runProg ${FNAME} && /app/runProg"
test:
	docker run \
	-v $(shell pwd)/tests:/app/tests \
	-v $(shell pwd)/src:/app/src \
	--rm \
	cppgd:latest \
	/bin/bash -c "g++ -std=c++11 -o /app/tests/some_test /app/src/*.cc /app/tests/*_test.cc && /app/tests/some_test && rm /app/tests/some_test"
