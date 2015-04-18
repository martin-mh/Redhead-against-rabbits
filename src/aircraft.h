#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "resourceidentifiers.h"
#include "command.h"
#include "commandqueue.h"
#include "projectile.h"
#include "textnode.h"

#include <string>

class Aircraft : public Entity
{
public:
    enum Type
    {
        Eagle,
        Raptor,
        Avenger,
        TypeCount
    };

public:
    Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts);

    virtual unsigned int getCategory() const;
    virtual sf::FloatRect getBoundingRect() const;
    virtual bool isMarkedForRemoval() const;
    bool isAllied() const;
    float getMaxSpeed() const;

    void increaseFireRate();
    void increaseSpread();
    void collectMissiles(unsigned int count);

    void fire();
    void launchMissile();

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
    void updateMovementPattern(sf::Time dt);
    void checkPickupDrop(CommandQueue& commands);
    void checkProjectileLaunch(sf::Time dt, CommandQueue& commands);

    void createBullets(SceneNode& node, const TextureHolder& textures) const;
    void createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const;
    void createPickup(SceneNode& node, const TextureHolder& textures) const;

    void updateTexts();

private:
    Type mType;
    sf::Sprite mSprite;
    Command mFireCommand;
    Command mMissileCommand;
    sf::Time mFireCountdown;
    bool mIsFiring;
    bool mIsLaunchingMissile;
    bool mIsMarkedForRemoval;

    int mFireRateLevel;
    int mSpreadLevel;
    int mMissileAmmo;

    Command mDropPickupCommand;
    float mTravelledDistance;
    std::size_t mDirectionIndex;
    TextNode* mHealthDisplay;
    TextNode* mMissileDisplay;
};

#endif // AIRCRAFT_H
