﻿#pragma once

class Mob {
public:
	int image[4];
	int size = 32;
	int sizeX = 128;
	int sizeY = 256;
	int x, y;
	int img;
	int img_num = 1;
	int muki = 3;

};

class Player {
public:
	int image[24];
	int size = 32;
	int sizeX = 128;
	int sizeY = 256;
	int x = size * 25, y = size * 15; //xを3940以内の32の倍数で指定
	int px = size * 25, py = size * 15; //xが832~2752のときは832固定
	int bx, by;
	int bpx, bpy;
	int img;
	int img_num = 1;
	int muki = 3;
	int walking_flag = 0;
	int walking_ani = 0;
	int walking_ani_flag = 0;
	int speed = 4;
	int money = 1000;
};

class Hatake {
public:
	int size = 128;
	int x, y;
	int img;
	int seeds;
	int level;

};

class Map {
public:
	void init() {
		map_image = LoadGraph("image/map.png", TRUE);
		sakanaya_image[0] = LoadGraph("image/sakanaya1.png", TRUE);
		sakanaya_image[1] = LoadGraph("image/sakanaya2.png", TRUE);
		sakanaya_image[2] = LoadGraph("image/sakanaya3.png", TRUE);
		yorozuya_image[0] = LoadGraph("image/yorozuya1.png", TRUE);
		yorozuya_image[1] = LoadGraph("image/yorozuya2.png", TRUE);
		yorozuya_image[2] = LoadGraph("image/yorozuya3.png", TRUE);
		farm_image[0] = LoadGraph("image/farm1.png", TRUE);
		farm_image[1] = LoadGraph("image/farm2.png", TRUE);
		farm_image[2] = LoadGraph("image/farm3.png", TRUE);
		farm_image[3] = LoadGraph("image/farm4.png", TRUE);
		tomato_image[0] = LoadGraph("image/tomato1.png", TRUE);
		tomato_image[1] = LoadGraph("image/tomato2.png", TRUE);
		tomato_image[2] = LoadGraph("image/tomato3.png", TRUE);
		kyabetsu_image[0] = LoadGraph("image/kyabetsu1.png", TRUE);
		kyabetsu_image[1] = LoadGraph("image/kyabetsu2.png", TRUE);
		kyabetsu_image[2] = LoadGraph("image/kyabetsu3.png", TRUE);
		morokoshi_image[0] = LoadGraph("image/morokoshi1.png", TRUE);
		morokoshi_image[1] = LoadGraph("image/morokoshi2.png", TRUE);
		morokoshi_image[2] = LoadGraph("image/morokoshi3.png", TRUE);
		hatake_image = LoadGraph("image/hatake.png", TRUE);
		icon_image = LoadGraph("image/ex_icon.png", TRUE);
		fish_icon_image = LoadGraph("image/fish_icon.png", TRUE);
		area_icon_image = LoadGraph("image/area_icon.png", TRUE);
		menu_image = LoadGraph("image/menu.png", TRUE);
		selector_image = LoadGraph("image/selector.png", TRUE);
		textwindow_image = LoadGraph("image/textwindow.png", TRUE);
		window_image = LoadGraph("image/window.png", TRUE);
		find_image = LoadGraph("image/find_fish.png", TRUE);

		LoadDivGraph("image/player.png", 24, 6, 4, player.sizeX, player.sizeY, player.image);//画像を分割してimage配列に保存
		LoadDivGraph("image/ji.png", 4, 1, 4, mob[0].sizeX, mob[0].sizeY, mob[0].image);//画像を分割してimage配列に保存
		LoadDivGraph("image/ba.png", 4, 1, 4, mob[1].sizeX, mob[1].sizeY, mob[1].image);//画像を分割してimage配列に保存
		
		bgm = LoadSoundMem("music/genkaivillage.wav");

		//Font
		FontHandle_mini = CreateFontToHandle(NULL, 20, 2, DX_FONTTYPE_EDGE);
		FontHandle = CreateFontToHandle(NULL, 50, 2, DX_FONTTYPE_EDGE);
		FontHandle_big = CreateFontToHandle(NULL, 70, 2, DX_FONTTYPE_EDGE);

		//おじいの初期位置
		mob[0].x = mob[0].size * 43;
		mob[0].y = mob[0].size * 13;
		mob[0].img = mob[0].image[0];

		//おばあの初期位置
		mob[1].x = mob[1].size * 18;
		mob[1].y = mob[1].size * 13;
		mob[1].img = mob[1].image[0];

		//畑の位置
		for (j = 0; j < 2; j++) {
			for (i = 0; i < 5; i++) {
				hatake[i + j * 5].x = 640 + chip_size * i;
				hatake[i + j * 5].y = 800 + chip_size * j;
				hatake[i + j * 5].img = hatake_image;
			}
		}
	}

	void call(std::array<int, item_num>& item_count, bool up_key[], std::int_fast32_t key[256], std::uint_fast8_t& scene_id, std::uint_fast32_t fished_count, std::uint_fast32_t go_fish_count, int& yorozuya_level, int& sakanaya_level, int& farm_level) {
		//キー入力
		eflag = 0;
		returnflag = 0;
		if (player.x % player.size == 0 && player.y % player.size == 0 && talk == 0 && menu == 0) {       //座標が32で割り切れたら入力可能
			player.walking_flag = 1;                  //歩くフラグを立てる。
			if ((key[KEY_INPUT_UP]  && key[KEY_INPUT_LEFT] ) || (key[KEY_INPUT_W]  && key[KEY_INPUT_A] ))
				player.muki = 1;
			else if (key[KEY_INPUT_LEFT]  && key[KEY_INPUT_DOWN]  || (key[KEY_INPUT_A]  && key[KEY_INPUT_S] ))
				player.muki = 3;
			else if (key[KEY_INPUT_DOWN]  && key[KEY_INPUT_RIGHT]  || (key[KEY_INPUT_S]  && key[KEY_INPUT_D] ))
				player.muki = 5;
			else if (key[KEY_INPUT_RIGHT]  && key[KEY_INPUT_UP]  || (key[KEY_INPUT_D]  && key[KEY_INPUT_W] ))
				player.muki = 7;
			else if (key[KEY_INPUT_UP]  || key[KEY_INPUT_W] )    //上ボタンが押されたら
				player.muki = 0;                       //上向きフラグを立てる
			else if (key[KEY_INPUT_LEFT]  || key[KEY_INPUT_A] )  //左ボタンが押されたら
				player.muki = 2;                       //左向きフラグを
			else if (key[KEY_INPUT_DOWN]  || key[KEY_INPUT_S] )  //下ボタンが押されたら
				player.muki = 4;                       //右向きフラグを立てる
			else if (key[KEY_INPUT_RIGHT]  || key[KEY_INPUT_D] ) //右ボタンが押されたら
				player.muki = 6;                       //下向きフラグを
			else                                      //何のボタンも押されてなかったら
				player.walking_flag = 0;              //歩かないフラグを立てる
		}		

		if (talk == 12) {
			if (up_key[KEY_INPUT_RETURN] && returnflag == 0) {
				talk = 0;
				returnflag = 1;
			}
		}
		else if (talk == 11) {
			if (up_key[KEY_INPUT_UP] || up_key[KEY_INPUT_W]) select4--, selector4_y -= 50;
			else if (up_key[KEY_INPUT_DOWN] || up_key[KEY_INPUT_S]) select4++, selector4_y += 50;
			if (select4 > 3) select4 = 0, selector4_y -= 200;
			if (select4 < 0) select4 = 3, selector4_y += 200;
			//決定
			if (up_key[KEY_INPUT_RETURN] && returnflag == 0) {
				talk = 12; 
				returnflag = 1;
				if (select4 == 0) 
					if (item_count[item_tomato_seed] > 0) {
						hatake[hatake_select].img = tomato_image[0];
						hatake[hatake_select].level = 0;
						item_count[item_tomato_seed]--;
				}
				if (select4 == 1) 
					if (item_count[item_cabbage_seed] > 0) {
						hatake[hatake_select].img = kyabetsu_image[0];
						hatake[hatake_select].level = 0;
						item_count[item_cabbage_seed]--;
					}
				if (select4 == 2)
					if (item_count[item_corn_seed] > 0) {
						hatake[hatake_select].img = morokoshi_image[0];
						hatake[hatake_select].level = 0;
						item_count[item_corn_seed]--;
					}
			}
		}
		//会話終了，メニュー閉じる
		else if ((talk >= 1 && (up_key[KEY_INPUT_RETURN]  && returnflag == 0)) && talk != 10 && talk != 2) {
			returnflag = 1;
			talk = 0;
		}
		else if (up_key[KEY_INPUT_E]  && menu >= 1 && eflag == 0 && talk == 0) {
			menu = 0;
			eflag = 1;
		}
		//よろず屋
		else if (talk == 2) {
			if (up_key[KEY_INPUT_RETURN] && returnflag == 0) {
				menu = 3;
			}
		}
		//メニュー画面
		else if (menu == 2) {
			if (key[KEY_INPUT_LEFT]  || key[KEY_INPUT_A] ) menu = 1;

			if (up_key[KEY_INPUT_UP]  || up_key[KEY_INPUT_W] ) select2--, selector2_y -= 70;
			else if (up_key[KEY_INPUT_DOWN]  || up_key[KEY_INPUT_S] ) select2++, selector2_y += 70;
			if (select2 > 3) select2 = 0, selector2_y -= 70;
			if (select2 < 0) select2 = 3, selector2_y += 70;
			//決定
			if ((key[KEY_INPUT_RIGHT]  || key[KEY_INPUT_D] ) && select2 == 0) menu = 2;
			if (up_key[KEY_INPUT_RETURN]  && returnflag == 0) {
				returnflag = 1;
				if (select2 == 0) menu = 2;
				if (select2 == 1) menu = 0;
				if (select2 == 2) scene_id = 1, menu = 0;
			}
		}
		else if ((up_key[KEY_INPUT_E]  || menu == 1) && eflag == 0 && talk == 0) {
			eflag = 1;
			menu = 1;
			if (up_key[KEY_INPUT_UP]  || up_key[KEY_INPUT_W] ) select--, selector_y -= 175;
			else if (up_key[KEY_INPUT_DOWN]  || up_key[KEY_INPUT_S] ) select++, selector_y += 175;
			if (select > 2) select = 0, selector_y -= 525;
			if (select < 0) select = 2, selector_y += 525;
			//決定
			if ((key[KEY_INPUT_RIGHT]  || key[KEY_INPUT_D] ) && select == 0) menu = 2;
			if (up_key[KEY_INPUT_RETURN]  && returnflag == 0) {
				returnflag = 1;
				if (select == 0) menu = 2;
				if (select == 1) menu = 0;
				if (select == 2) scene_id = 1, menu = 0;
			}
		}
		//釣り場移行
		else if (player.x > tsuri_area) {
			if (up_key[KEY_INPUT_RETURN]  && returnflag == 0) {
				returnflag = 1;
				StopSoundMem(bgm);
				scene_id = 3;
			}
		}
		//モブとの会話
		else {
			for (i = 0; i < mob_num; i++) {
				if (player.x + player.sizeX * 2 > mob[i].x &&
					player.x < mob[i].x + mob[i].sizeX * 2 &&
					player.y + player.sizeY > mob[i].y &&
					player.y < mob[i].y + mob[i].sizeY / 2) {
					//近づいた状態で話しかける
					if ((up_key[KEY_INPUT_RETURN]  && returnflag == 0) || talk >= 1) {
						returnflag = 1;

						if (talk == 0) {
							talk = i+1;
							//モブの振り向き
							if (player.x + player.sizeX/2 < mob[i].x) mob[i].img = mob[i].image[1];
							else if (player.x + player.sizeX/2 > mob[i].x + player.sizeX) mob[i].img = mob[i].image[2];
							else if (player.y < mob[i].y + mob[i].sizeY / 4) mob[i].img = mob[i].image[3];
							else mob[i].img = mob[i].image[0];
						}
						break;
					}
				}
			}
			//hatake
			if (up_key[KEY_INPUT_RETURN] && returnflag == 0 && talk == 10) {
				talk = 11;

			}
			else {
				for (j = 0; j < 10; j++) {
					if (player.x + player.sizeX - 32 > hatake[j].x &&
						player.x < hatake[j].x + hatake[j].size - 32 &&
						player.y + player.sizeY / 2 > hatake[j].y - 128 &&
						player.y < hatake[j].y + hatake[j].size / 2 - 128) {
						hatake_find = j;
						//近づいた状態で話しかける
						if ((up_key[KEY_INPUT_RETURN]  && returnflag == 0) || talk >= 1) {
							returnflag = 1;
							if (talk == 0) {
								talk = 10;
								hatake_select = j;
								break;
							}
						}
					}
				}
			}
			
		}

		//移動処理
		if (player.walking_flag == 1) {       //歩くフラグが立っていたら
			if (player.muki == 0)             //上向きならy座標を減らす
				player.y-= player.speed, player.img_num = 19;
			else if (player.muki == 1)
				player.x-= player.speed, player.y-= player.speed, player.img_num = 16;
			else if (player.muki == 2)        //左向きならx座標を減らす
				player.x-= player.speed, player.img_num = 7;
			else if (player.muki == 3)
				player.x-= player.speed, player.y+= player.speed, player.img_num = 4;
			else if (player.muki == 4)        //下向きならy座標を増やす
				player.y+= player.speed, player.img_num = 1;
			else if (player.muki == 5)
				player.x+= player.speed, player.y+= player.speed, player.img_num = 10;
			else if (player.muki == 6)        //右向きならx座標を増やす
				player.x+= player.speed, player.img_num = 13;
			else if (player.muki == 7)
				player.x+= player.speed, player.y-= player.speed, player.img_num = 22;
		
			if (player.x <= map_width / 2 - player.sizeX || player.x >= map_width + map_width / 2 - player.sizeX) {   //プレイヤーのみ動かす
				if (player.muki == 0)
					player.py-= player.speed;
				else if (player.muki == 1)
					player.px-= player.speed, player.py-= player.speed;
				else if (player.muki == 2)
					player.px-= player.speed;
				else if (player.muki == 3)
					player.px-= player.speed, player.py+= player.speed;
				else if (player.muki == 4)
					player.py+= player.speed;
				else if (player.muki == 5)
					player.px+= player.speed, player.py+= player.speed;
				else if (player.muki == 6)
					player.px+= player.speed;
				else if (player.muki == 7)
					player.px+= player.speed, player.py-= player.speed;
			}
			else {  //背景を追従させる(プレイヤーのx座標固定)
				if (player.muki == 0)
					player.py-= player.speed;
				else if (player.muki == 1)
					player.py-= player.speed;
				else if (player.muki == 3)
					player.py+= player.speed;
				else if (player.muki == 4)
					player.py+= player.speed;
				else if (player.muki == 5)
					player.py+= player.speed;
				else if (player.muki == 7)
					player.py-= player.speed;
			}
		}

		//カメラ追従
		if (player.x <= map_width / 2 - player.sizeX) background_x = 0;
		else if (player.x >= map_width + map_width / 2 - player.sizeX) background_x = -map_width;
		else background_x = map_width / 2 - player.sizeX - player.x;

		//進入禁止エリアの指定
		if (player.x < 0) player.x = player.bx, player.px = player.bpx;
		else if (player.x > player.size*110 && player.px > player.size * 48) player.x = player.bx, player.px = player.bpx;
		if (player.y < player.size * 13) player.y = player.by, player.py = player.bpy;
		else if (player.y > player.size*26) player.y = player.by, player.py = player.bpy;
		
		//Mobとの当たり判定
		for (i = 0; i < mob_num; i++) {
			if (player.x + player.sizeX > mob[i].x &&
				player.x < mob[i].x + mob[i].sizeX &&
				player.y + player.sizeY / 4 > mob[i].y &&
				player.y < mob[i].y + mob[i].sizeY / 4) {
				player.px = player.bpx, player.x = player.bx, player.py = player.bpy, player.y = player.by;
			}
		}
		//畑の当たり判定
		for (i = 0; i < hatake_num; i++) {
			if (player.x + player.sizeX > hatake[i].x &&
				player.x < hatake[i].x + hatake[i].size &&
				player.y + player.sizeY / 4 > hatake[i].y - 128 &&
				player.y < hatake[i].y + hatake[i].size / 4 - 128) {
				player.px = player.bpx, player.x = player.bx, player.py = player.bpy, player.y = player.by;
			}
		}

		//プレイヤーの歩行アニメーション
		if ((player.x % 32 == 0 && player.y % 32 == 0) && player.walking_ani_flag == 0) {
			if (player.px % 32 != 0) {
				if (player.bpx > player.px) player.px += player.speed;
				else if (player.bpx < player.px) player.px -= player.speed;
			}
			player.walking_ani++;
			player.walking_ani_flag = 1;
		}
		else if (player.bx != player.x || player.by != player.y) {
			player.walking_ani_flag = 0;
		}
		if (player.walking_ani == 200) player.walking_ani = 0;

		if (player.x % 32 == 0 && player.y % 32 == 0) player.img = player.image[player.img_num];
		else if (player.walking_ani % 4 == 0) player.img = player.image[player.img_num - 1];
		else if (player.walking_ani % 4 == 1) player.img = player.image[player.img_num];
		else if (player.walking_ani % 4 == 2) player.img = player.image[player.img_num + 1];
		else if (player.walking_ani % 4 == 3) player.img = player.image[player.img_num];
			
		
		//モード推移後のフラグ処理
		if (go_fish_count != go_fish_before) {
			sakana_total += fished_count;
			bgm_flag = 0;
		}

		//集落レベルの管理
		if (sakana_total >= 100) sakanaya_level = 2;
		else if (sakana_total >= 30) sakanaya_level = 1;
		
        //BGM再生
		if (bgm_flag == 0) {
			PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
			bgm_flag = 1;
		}

		//前フレームのデータを記録
		player.bpx = player.px;
		player.bpy = player.py;
		player.bx = player.x;
		player.by = player.y;
		go_fish_before = go_fish_count;

		Draw(yorozuya_level, sakanaya_level, farm_level, item_count);

		printfDx("%d \n", talk);
		if (talk == 0 && menu == 0) {
			selector_y = 320;
			selector2_y = 0;
			selector3_y = 0;
			selector4_y = 600;
			select = 0;
			select2 = 0;
			select3 = 0;
			select4 = 0;
		}
	}

	void Draw(int yorozuya_level, int sakanaya_level, int farm_level, std::array<int, item_num>& item_count) {
		//背景を描画
		DrawGraph(background_x, 0, map_image, TRUE);
		DrawGraph(background_x, 0, yorozuya_image[yorozuya_level], TRUE);
		DrawGraph(background_x, 0, sakanaya_image[sakanaya_level], TRUE);
		DrawGraph(background_x, 0, farm_image[farm_level], TRUE);

		//つりエリアのアイコン表示
		if (player.x > tsuri_area) {
			DrawGraph(0, 0, area_icon_image, TRUE);
			DrawGraph(tsuri_area + background_x - 400, -250, fish_icon_image, TRUE);
			DrawFormatStringToHandle(1050, 200, GetColor(0, 0, 0), FontHandle, "Enterキーで釣りエリアへ");
		}
		//おじいのアイコンを描画
		DrawGraph(mob[0].x + background_x - 64, mob[0].y - 200, icon_image, TRUE);

		//後方のものから表示
		for (i = 0; i < mob_num; i++)
			if (mob[i].y <= player.y)
				if (mob[i].x > player.x - map_width && mob[i].x < player.x + map_width) DrawGraph(mob[i].x + background_x, mob[i].y, mob[i].img, TRUE);//jiを描画
		for (i = 0; i < hatake_num; i++)
			if (hatake[i].y + hatake[i].size/ 2 <= player.y + player.sizeY)
				if (hatake[i].x > player.x - map_width && hatake[i].x < player.x + map_width) DrawGraph(hatake[i].x + background_x, hatake[i].y, hatake[i].img, TRUE);//hatake
		DrawGraph(player.px, player.py, player.img, TRUE);   //プレイヤーを描画
		for (i = 0; i < mob_num; i++)
			if (mob[i].y > player.y)
				if (mob[i].x > player.x - map_width && mob[i].x < player.x + map_width)  DrawGraph(mob[i].x + background_x, mob[i].y, mob[i].img, TRUE);  //jiを描画
		for (i = 0; i < hatake_num; i++)
			if (hatake[i].y + hatake[i].size / 2 > player.y + player.sizeY)
				if (hatake[i].x > player.x - map_width && hatake[i].x < player.x + map_width)  DrawGraph(hatake[i].x + background_x, hatake[i].y, hatake[i].img, TRUE);  //hatake

		//メニューの描画
		if (menu == 1 || menu == 2) {
			DrawGraph(0, 0, menu_image, TRUE);
			DrawGraph(125, selector_y, selector_image, TRUE);
			DrawFormatStringToHandle(250, 145, GetColor(0, 0, 0), FontHandle, "%d", player.money);

			DrawFormatStringToHandle(600, 180, GetColor(255, 255, 255), FontHandle, "%s", item_name[select2+1]);
			DrawFormatStringToHandle(600, 250, GetColor(255, 255, 255), FontHandle, "%s", item_name[select2+2]);
			DrawFormatStringToHandle(600, 320, GetColor(255, 255, 255), FontHandle, "%s", item_name[select2+3]);
			DrawFormatStringToHandle(600, 390, GetColor(255, 255, 255), FontHandle, "%s", item_name[select2+4]);
			if (menu == 2) {
				DrawGraph(380, selector2_y, selector_image, TRUE);

			}
		}
		else if(menu == 3) {
			DrawGraph(0, 0, menu_image, TRUE);
			DrawGraph(125, selector_y, selector_image, TRUE);
			DrawFormatStringToHandle(250, 145, GetColor(0, 0, 0), FontHandle, "%d", player.money);

			DrawFormatStringToHandle(600, 180, GetColor(255, 255, 255), FontHandle, "%s", item_name[select2 + 1]);
			DrawFormatStringToHandle(600, 250, GetColor(255, 255, 255), FontHandle, "%s", item_name[select2 + 2]);
			DrawFormatStringToHandle(600, 320, GetColor(255, 255, 255), FontHandle, "%s", item_name[select2 + 3]);
			DrawFormatStringToHandle(600, 390, GetColor(255, 255, 255), FontHandle, "%s", item_name[select2 + 4]);
		}

		//テキストボックス
		if(talk >= 1) {
			DrawGraph(0, 0, textwindow_image, TRUE);
			if (talk == 1) {
				DrawFormatStringToHandle(130, 815, GetColor(255, 255, 255), FontHandle, "釣りをしてこの集落を復興させてくれ！");
				DrawFormatStringToHandle(240, 730, GetColor(255, 255, 255), FontHandle, "祖父");
			}
			else if (talk == 2) {
				DrawFormatStringToHandle(130, 815, GetColor(255, 255, 255), FontHandle, "なんか用？");
				DrawFormatStringToHandle(130, 875, GetColor(255, 255, 255), FontHandle, "");
				DrawFormatStringToHandle(190, 730, GetColor(255, 255, 255), FontHandle, "よろず屋");
			}
			else if (talk == 10) {
				DrawFormatStringToHandle(130, 815, GetColor(255, 255, 255), FontHandle, "植える種を選んでください");
				DrawFormatStringToHandle(275, 730, GetColor(255, 255, 255), FontHandle, "畑");
			}
			else if (talk == 11) {
				DrawFormatStringToHandle(130, 815, GetColor(255, 255, 255), FontHandle, "植える種を選んでください");
				DrawFormatStringToHandle(275, 730, GetColor(255, 255, 255), FontHandle, "畑");
				DrawGraph(0, 0, window_image, TRUE);
				DrawRotaGraph(1440, selector4_y, 0.5, 0, selector_image, TRUE, FALSE);
				DrawFormatStringToHandle(1470, 600, GetColor(0, 0, 0), FontHandle_mini, "トマトの種 ×%d", item_count[item_tomato_seed]);
				DrawFormatStringToHandle(1470, 650, GetColor(0, 0, 0), FontHandle_mini, "キャベツの種 ×%d", item_count[item_cabbage_seed]);
				DrawFormatStringToHandle(1470, 700, GetColor(0, 0, 0), FontHandle_mini, "とうもろこしの種 ×%d", item_count[item_corn_seed]);
				DrawFormatStringToHandle(1470, 750, GetColor(0, 0, 0), FontHandle_mini, "やめる");
			}
			else if (talk == 12) {
				DrawFormatStringToHandle(130, 815, GetColor(255, 255, 255), FontHandle, "育つまでミニゲームで遊ぼう");
				DrawFormatStringToHandle(275, 730, GetColor(255, 255, 255), FontHandle, "畑");
			}
		}

		if (hatake_find != 10) {
			DrawRotaGraph(hatake[hatake_find].x + background_x + 64, hatake[hatake_find].y + 96, 0.3, 0, find_image, TRUE, FALSE);
		}
	
	}

private:
	Mob mob[2];
	Player player;
	Hatake hatake[10];

	std::uint_fast32_t go_fish_before = 0;
	int i, j;
	int mob_num = 3;
	int hatake_num = 10;
	int select = 0;
	int select2 = 0;
	int select3 = 0;
	int select4 = 0;
	int FontHandle;
	int FontHandle_mini;
	int FontHandle_big;
	int sakana_total = 0;
	int item_select = 0;
	int hatake_select = 0;

	//flag
	int bgm, bgm_flag = 0;
	int talk = 0;
	int menu = 0;
	int eflag = 0;
	int returnflag = 0;
	int hatake_find = 10;

	//image
	int map_image;
	int sakanaya_image[3];
	int yorozuya_image[3];
	int farm_image[4];
	int tomato_image[3];
	int kyabetsu_image[3];
	int morokoshi_image[3];
	int hatake_image;
	int area_icon_image;
	int fish_icon_image;
	int icon_image;
	int menu_image;
    int selector_image;
	int textwindow_image;
	int window_image;
	int find_image;
	int menu2_image;

	//座標
	int background_x = 0;
	int selector_y = 320;
	int selector2_y = 0;
	int selector3_y = 0;
	int selector4_y = 600;
	int tsuri_area = 2800;


	int chip_size = 128;
	int map_width = 1920;//3840 120
	int map_hight = 1080;//640 20

};
