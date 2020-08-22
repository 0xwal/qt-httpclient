
docker ps | grep httpbin || (docker pull kennethreitz/httpbin && docker run -p 80:80 -d kennethreitz/httpbin)

