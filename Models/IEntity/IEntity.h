#ifndef IENTITY_H
#define IENTITY_H

class IEntity {
public:
  virtual IEntity *copy() const = 0;
  virtual void assign(const IEntity &other) = 0;
  virtual void destroy() = 0;

  virtual void showInfo() const = 0;
  virtual bool isEqual(const IEntity &other) const = 0;

  virtual ~IEntity() = default;
};

#endif
