#pragma once
#include "redis/abstract_command.hh"
#include "redis/request.hh"
#include "redis/commands/append.hh"

class timeout_config;
namespace redis {
namespace commands {
class counter final : public append {
    bool _incr;
    long _step;
public:
    struct incr_tag {};
    struct decr_tag {};
    struct incrby_tag {};
    struct decrby_tag {};
    static shared_ptr<abstract_command> prepare(service::storage_proxy& proxy, incr_tag tag, request&& req);
    static shared_ptr<abstract_command> prepare(service::storage_proxy& proxy, decr_tag tag, request&& req);
    static shared_ptr<abstract_command> prepare(service::storage_proxy& proxy, incrby_tag tag, request&& req);
    static shared_ptr<abstract_command> prepare(service::storage_proxy& proxy, decrby_tag tag, request&& req);
    counter(bytes&& name, const schema_ptr schema, bytes&& key, bytes&& data, bool incr) : append(std::move(name), schema, std::move(key), std::move(data)), _incr(incr)
    {
    }
    ~counter() {}
    future<reply> execute(service::storage_proxy&, db::consistency_level, db::timeout_clock::time_point, const timeout_config& tc, service::client_state& cs) override;
};
}
}
