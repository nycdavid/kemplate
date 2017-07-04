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
