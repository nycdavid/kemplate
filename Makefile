image:
	docker build \
	-t cppgd \
	.
compile:
	docker run \
	-v $(shell pwd):/app \
	--rm \
	cppgd:latest \
	/bin/ash -c "g++ -o /app/runProg ${FNAME} && /app/runProg"
