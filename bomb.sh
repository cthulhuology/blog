
COUNT=$1
URL=$2

if [[ -z "$URL" ]]; then
	URL=localhost:8080
fi

test(){
	START=`date`
	for I in `seq 1000`; do curl -s $URL >/dev/null; done	
	END=`date`
	echo "$START - $END"
}

for I in `seq $COUNT`; do 
	test &
done
