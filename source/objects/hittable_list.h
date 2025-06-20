#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.hpp"

#include <memory>
#include <vector>

class hittable_list : public hittable {
 public:
  hittable_list() = default;
  explicit hittable_list(std::shared_ptr<hittable> object) { add(object); }

  void clear() { objects.clear(); }
  void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

  std::vector<std::shared_ptr<hittable>> objects;
};
#endif
