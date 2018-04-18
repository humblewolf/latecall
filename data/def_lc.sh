echo "This default latecall script will delete any docker container, change this as per your requirements.\n"
# Delete every Docker containers
# Must be run first because images are attached to containers
docker rm $(docker ps -a -q)

# Delete every Docker image
docker rmi $(docker images -q)