FROM gcc:13

# Install required libraries
RUN apt-get update && apt-get install -y \
    libsqlite3-dev \
    libcurl4-openssl-dev \
    nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN g++ -std=c++17 Classes/*.cpp main.cpp \
    -IClasses/headers \
    -o app \
    -lsqlite3 -lcurl

CMD ["./app"]