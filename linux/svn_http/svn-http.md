subversion http配置
==================

## 1. 安装svn

yum install httpd httpd-devel subversion mod_dav_svn

确定已经安装了svn模块：mod_dav_svn

mod_authz_svn.so
mod_dav_svn.so

## 2. 创建仓库，修改svn配置文件

1. 加载模块

```
cd /etc/httpd/conf.d
[root@svn conf.d]# vim subversion.conf
添加以下二行
LoadModule dav_svn_module     modules/mod_dav_svn.so
LoadModule authz_svn_module   modules/mod_authz_svn.so
```

2. 创建仓库，以及仓库目录的设置

```
mkdir -p /data/svn
cd /data/svn
svnadmin create repos
chown -R apache:apache repos
```

** 开机启动svn **

vim /etc/rc.d/rc.local  ###添加以下内容
`/usr/local/svn/bin/svnserve -d -r /data/svn`

3. 编辑/etc/httpd/conf.d/subversion.conf

`vi /etc/httpd/conf.d/subversion.conf`

```
LoadModule dav_svn_module    modules/mod_dav_svn.so
LoadModule authz_svn_module  modules/mod_authz_svn.so

<Location /svn>
    DAV svn
    SVNParentPath /data/svn
    SVNListParentPath on
    AuthType Basic
    AuthName "Subversion repos"
    AuthzSVNAccessFile /data/svn/conf/authz.conf
    AuthUserFile /data/conf/svn_http_passwd
    Require valid-user
</Location>
```
保存

** 开机启动httpd服务**

`vim /etc/rc.d/rc.local`

添加以下内容
`systemctrl start httpd.service`

4. 添加用户

* 创建用户：
  `htpasswd -c /data/svn/conf/svn_http_passwd yourname`
* 添加用户
  `htpasswd /data/svn/conf/svn_http_passwd yourname`

5. 重启httpd服务

`service httpd restart`

**关闭防火墙及对应端口**

** 关闭SElinux **

```
cd /etc/selinx
vim config
```
编辑`ELINUX=disabled`
保存退出并reboot




