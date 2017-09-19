package(default_visibility = ["//visibility:public"])

load("@protobuf//:protobuf.bzl", "cc_proto_library")

cc_binary(
  name = "sofa_rpc_server",
  srcs = glob([
    "src/*.h",
    "src/server.cc",
  ]),
  deps = [
    ":cc_protos",
    "@sofa//:sofa-pbrpc",
    "@sudoku//:sudoku",
    "@protobuf//:protobuf",
  ],
)

cc_binary(
  name = "sofa_rpc_client",
  srcs = glob([
    "src/*.h",
    "src/client.cc",
  ]),
  deps = [
    ":cc_protos",
    "@sofa//:sofa-pbrpc",
    "@sudoku//:sudoku",
    "@protobuf//:protobuf",
  ],
)

cc_proto_library(
  name = "cc_protos",
  srcs = ["src/sudoku_service.proto"],
  include = "src/",
  default_runtime = "@protobuf//:protobuf",
  protoc = "@protobuf//:protoc",
  deps = ["@protobuf//:cc_wkt_protos"],
)


