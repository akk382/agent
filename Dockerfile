FROM gcc:latest AS agent
RUN apt update \
    && wget -qO - http://packages.confluent.io/deb/3.3/archive.key | apt-key add - \
    && apt install -y software-properties-common \
    && add-apt-repository -y "deb [arch=amd64] http://packages.confluent.io/deb/3.3 stable main" \
    && apt-get update && apt-get install -y librdkafka1 librdkafka-dev \
    && apt install -y cmake libcjson1

RUN wget https://github.com/Kitware/CMake/releases/download/v3.30.0/cmake-3.30.0-linux-x86_64.sh \
    && bash cmake-3.30.0-linux-x86_64.sh --prefix=/usr/local --skip-license \
    && rm cmake-3.30.0-linux-x86_64.sh

RUN wget https://github.com/DaveGamble/cJSON/archive/refs/tags/v1.7.18.zip \
    && unzip v1.7.18.zip \
    && mv cJSON* cJSON

COPY . /usr/src/agent
WORKDIR /usr/src/agent
RUN cp /cJSON/cJSON.c /cJSON/cJSON.h .
RUN mkdir build && cd build && cmake /usr/src/agent && cmake --build .
CMD ["bash", "-c", "build/agent_exec"]