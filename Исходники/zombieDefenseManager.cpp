void ZombieDefenseManager::makeBullet(const Sprite& shooter, const Sprite& target) { 	   
   Vector2D origins = shooter.getCoordinate();
   origins[0] += (shooter.getFrame()->getWidth() / 2);
   origins[1] += (shooter.getFrame()->getHeight() / 2);
   float radius = shooter.getFrame()->getWidth() / 2 + shooter.getFrame()->getHeight() / 2;
   Vector2D shoot = target.getCoordinate() - origins;
   shoot.normalize();
   origins += radius * shoot;
   bullets.push_back(Bullet(origins, shoot * game->getBulletSpeed(), fact->getFrame(bulletSurfaceString)));
}