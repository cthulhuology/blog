
COUNT=$1

test(){
	START=`date`
	for I in `seq 1000`; do curl localhost:8080; done	
	END=`date`
	echo "$START - $END"
}

for I in `seq $COUNT`; do 
	test &
done
