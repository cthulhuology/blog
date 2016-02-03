#!/bin/bash

while true; do
	curl -s localhost:8080/  > /dev/null
	sleep 10
done

