// Spawner is not necessarily parent, in case of subunits/fighters
bool Bullet::Initialize(Unit *spawner, int player_, int direction, WeaponType weapon, const Point &pos)
{
    Assert(!bulletframes_in_progress);
    list.prev = nullptr;
    list.next = nullptr;

    move_target = Point(0xffff, 0xffff);
    current_speed = 0;

    // Yes, bw mixes bullet's images with spawner's unit code.
    // At least wraith's lasers actually depend on this behaviour.
    const char *desc = "Bullet::Initialize (First frame of bullet's animation modifies the unit who spawned it)";
    UnitIscriptContext ctx(spawner, nullptr, desc, MainRng(), false);
    bool success = ((Flingy *)this)->Initialize(&ctx, weapon.Flingy(), player_, direction, pos);
    if (!success)
        return false;

    player = player_;
    Assert(weapon.Raw() < 0x100);
    weapon_id = (uint8_t)weapon.Raw();
    time_remaining = weapon.DeathTime();
    flingy_flags |= 0x8;
    flags = 0;
    bounces_remaining = 0;
    // Bw calls State_Init here, it should just return instantly though as no iscript has been run
    order_signal = 0;
    auto spin = weapon.LaunchSpin();
    if (spin != 0)
    {
        bool spin_positive = MainRng()->Rand(2) == 1;
        // Goliath dual missiles etc, ugh
        static bool last_bullet_spin_positive;
        if (spawner == *bw::last_bullet_spawner)
            spin_positive = !last_bullet_spin_positive;
        last_bullet_spin_positive = spin_positive;
        if (!spin_positive)
            spin = 0 - spin;
        movement_direction += spin;
        facing_direction = movement_direction;
        *bw::last_bullet_spawner = spawner;
    }

    if (spawner->Type().IsSubunit())
        parent = spawner->subunit;
    else if (spawner->Type() == UnitId::Scarab)
        parent = spawner->interceptor.parent;
    else
        parent = spawner;

    if (parent) // Parent may be nullptr if scara is shot and reaver dies before hit
        spawned.Add(parent->spawned_bullets);
    if (spawner->flags & UnitStatus::Hallucination)
        flags |= 0x2;
    previous_target = nullptr;
    target = spawner->target;
    if (target)
    {
        order_target_pos = target->sprite->position;
        sprite->elevation = target->sprite->elevation + 1;
        SetTarget(target);
    }
    else
    {
        order_target_pos = spawner->order_target_pos;
        sprite->elevation = spawner->sprite->elevation + 1;
    }

    switch (weapon.Behaviour())
    {
        case 0x8: // Move near
        {
            Assert(spawner->bullet_spread_seed < 0x100);
            spread_seed = (uint8_t)spawner->bullet_spread_seed;
            spawner->bullet_spread_seed++;
            if (spawner->bullet_spread_seed >= sizeof random_chances / sizeof(random_chances[0]))
                spawner->bullet_spread_seed = 0;
            const Point32 &diff = random_chances[spread_seed];
            Point &pos = order_target_pos;
            int x = min((int)*bw::map_width - 1, max(0, (int)pos.x - diff.x));
            int y = min((int)*bw::map_height - 1, max(0, (int)pos.y - diff.y));
            order_target_pos = Point(x, y);
            UpdateMoveTarget(order_target_pos);
        }
        break;
        case 0x2: case 0x4: // Appear on target unit / site
        if (target && parent)
        {
            if (MainRng()->Rand(0x100) <= bw::GetMissChance(parent, target))
            {
                int x = sprite->position.x - bw::circle[direction][0] * 30 / 256;
                int y = sprite->position.y - bw::circle[direction][1] * 30 / 256;
                x = max(0, min((int)*bw::map_width - 1, (int)x));
                y = max(0, min((int)*bw::map_height - 1, (int)y));
                Move(Point(x, y));
                flags |= 0x1;
            }
        }
        break;
        case 0x3: // Persist on target site
            Move(order_target_pos);
        break;
        case 0x6: // Suicide
        if (parent)
        {
            parent->flags |= UnitStatus::SelfDestructing;
            parent->Remove(nullptr);
        }
        break;
        case 0x9: // Go to max range
        {
            auto max_range = (Type().MaxRange() + 20) * 256;
            auto x = bw::circle[facing_direction][0] * max_range / 65536;
            auto y = bw::circle[facing_direction][1] * max_range / 65536;
            order_target_pos = spawner->sprite->position + Point(x, y);
            UpdateMoveTarget(order_target_pos);
        }
        break;
        case 0x7: case 0x1: case 0x0: // Bounce, Fly & follow/don't
            bounces_remaining = 3; // Won't matter on others
            if (target && parent)
            {
                if (MainRng()->Rand(0x100) <= bw::GetMissChance(parent, target))
                {
                    int x = order_target_pos.x - bw::circle[direction][0] * 30 / 256;
                    int y = order_target_pos.y - bw::circle[direction][1] * 30 / 256;
                    x = max(0, min((int)*bw::map_width - 1, (int)x));
                    y = max(0, min((int)*bw::map_height - 1, (int)y));
                    order_target_pos = Point(x, y);
                    flags |= 0x1;
                }
            }
            UpdateMoveTarget(order_target_pos);
        break;
        case 0x5: // Appear on attacker
        break;
        default:
            Warning("Unknown weapons.dat behaviour %x for weapon %x", Type().Behaviour(), weapon_id);
            return false;
        break;
    }
    return true;
}