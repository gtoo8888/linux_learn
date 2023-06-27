read -p "(Y/N)" yn
[ "${yn}" == "Y" -o "${yn}" == "y" ]  && echo "OK,continue" && exit 0
echo "I dont konw" && exit 0
