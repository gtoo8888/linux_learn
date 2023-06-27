until [ "${yn}" == "yes" -a "${yn}" == "YES" ]
do
	read -p "input:" yn
done
echo "OK!"
