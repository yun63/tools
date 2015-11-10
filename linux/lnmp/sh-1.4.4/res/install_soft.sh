#!/bin/bash

#phpwind
if [ ! -f phpwind_GBK_8.7.zip ];then
  wget http://oss.aliyuncs.com/aliyunecs/onekey/phpwind_GBK_8.7.zip
fi
rm -rf phpwind_GBK_8.7
unzip phpwind_GBK_8.7.zip
mv phpwind_GBK_8.7/upload/* /alidata/www/phpwind/
chmod -R 777 /alidata/www/phpwind/attachment
chmod -R 777 /alidata/www/phpwind/data
chmod -R 777 /alidata/www/phpwind/html
cd /alidata/www/phpwind/
find ./ -type f | xargs chmod 644
find ./ -type d | xargs chmod 755
chmod -R 777 attachment/ html/ data/
cd -

#phpmyadmin
if [ "$php_version" == "5.2.17" ];then
   if [ ! -f phpmyadmin.zip ];then
     http://zy-res.oss-cn-hangzhou.aliyuncs.com/php-5.2/phpMyAdmin-4.0.10.10-all-languages.zip
   fi
   rm -rf phpMyAdmin-4.0.10.10-all-languages
   unzip phpMyAdmin-4.0.10.10-all-languages.zip
   mv phpMyAdmin-4.0.10.10-all-languages /alidata/www/phpwind/phpmyadmin
else 
   if [ ! -f phpmyadmin.zip ];then
    wget http://oss.aliyuncs.com/aliyunecs/onekey/phpMyAdmin-4.1.8-all-languages.zip
   fi
   rm -rf phpMyAdmin-4.1.8-all-languages
   unzip phpMyAdmin-4.1.8-all-languages.zip
   mv phpMyAdmin-4.1.8-all-languages /alidata/www/phpwind/phpmyadmin
fi

chown -R www:www /alidata/www/phpwind/