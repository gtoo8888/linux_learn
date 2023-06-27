read -p "input: " nu
s=0
for (( i=1;i<=${nu};i=i+1))
do
	s=$((${s}+${i}))
done
echo "${s}"
